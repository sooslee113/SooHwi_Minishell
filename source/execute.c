/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:20:30 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 03:03:03 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	is_builtin(char *command)
// {
// 	if (ft_strcmp(command, "echo") == 0 ||
// 		ft_strcmp(command, "cd") == 0 ||
// 		ft_strcmp(command, "pwd") == 0 ||
// 		ft_strcmp(command, "export") == 0 ||
// 		ft_strcmp(command, "unset") == 0 ||
// 		ft_strcmp(command, "env") == 0 ||
// 		ft_strcmp(command, "exit") == 0)
// 		return (1);
// 	return (0);
// }

// void	execute_builtin(t_cmd *curr_cmd, char **envp)
// {
// 	if (ft_strcmp(curr_cmd->con, "echo") == 0)
// 		ft_echo(curr_cmd->args); // echo 구현 함수
// 	else if (ft_strcmp(curr_cmd->con, "cd") == 0)
// 		ft_cd(curr_cmd->args); // cd 구현 함수
// 	else if (ft_strcmp(curr_cmd->con, "pwd") == 0)
// 		ft_pwd(); // pwd 구현 함수
// 	else if (ft_strcmp(curr_cmd->con, "export") == 0)
// 		ft_export(curr_cmd->args, envp); // export 구현 함수
// 	else if (ft_strcmp(curr_cmd->con, "unset") == 0)
// 		ft_unset(curr_cmd->args, envp); // unset 구현 함수
// 	else if (ft_strcmp(curr_cmd->con, "env") == 0)
// 		ft_env(envp); // env 구현 함수
// 	else if (ft_strcmp(curr_cmd->con, "exit") == 0)
// 		ft_exit(curr_cmd->args); // exit 구현 함수
// 	else
// 	{
// 		printf("Command not found: %s\n", curr_cmd->con);
// 		exit(EXIT_FAILURE);
// 	}
// }

////////////////////////////////////////////////////////////////////////////////

char	*find_command_path(char *command, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = get_env_paths(envp); // 환경변수 PATH에서 경로 목록 가져오기
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, X_OK) == 0) // 실행 가능한 파일인지 확인
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	execute_external(t_cmd *curr_cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*command_path;

	command_path = find_command_path(curr_cmd->con, envp);
	if (!command_path)
	{
		printf("Command not found: %s\n", curr_cmd->con);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0) // 자식 프로세스
	{
		if (execve(command_path, curr_cmd->args, envp) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0) // 부모 프로세스
	{
		waitpid(pid, &status, 0); // 자식 프로세스 종료 대기
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			printf("Command failed with status: %d\n", WEXITSTATUS(status));
	}
	else // fork 실패
	{
		perror("Error creating process");
		exit(EXIT_FAILURE);
	}
	free(command_path);
}

////////////////////////////////////////////////////////////////////////////////

void	execute(t_sh *sh_list, char **envp)
{
	t_cmd	*curr_cmd;
	int		pre_fd;		// 이전 프로세스의 출력 파이프
	int		status;

	curr_cmd = sh_list->head_cmd;
	pre_fd = -1;			// 첫 번째 명령어는 입력이 없음

	while (curr_cmd != NULL)
	{
		if (curr_cmd->type == N_PIP) // '|'는 건너뜀
			curr_cmd = curr_cmd->next;
		// else if (curr_cmd->type == N_RED_OUT || curr_cmd->type == N_RED_OUT_AP || \
		// 	curr_cmd->type == N_RED_IN || curr_cmd->type == N_RED_HRDC) // 리다이렉션 처리
		// 	handle_redirection(&curr_cmd);
		else// 일반 명령어일 경우 실행 시작!
		{
			// [파이프가 필요할 경우 생성]
			if (curr_cmd->next && curr_cmd->next->type == N_PIP)
				pipe(sh_list->ad_cmd->pipe_fd);

			sh_list->ad_cmd->pid = fork(); // 프로세스 생성
			if (sh_list->ad_cmd->pid == 0) // [자식 프로세스]
			{
				
				// [이전 프로세스의 출력과 연결]
				if (pre_fd != -1)// 처음이 아닐 때(이전 OUT을 현재 IN으로 연결)
				{
					dup2(pre_fd, STDIN_FILENO);//이전 fd를 현재프로세스의 IN으로 덮기
					close(pre_fd);//이전은 닫아주기
				}

				// [다음 프로세스와 연결될 경우 파이프 출력 설정]
				if (curr_cmd->next && curr_cmd->next->type == N_PIP)
				{
					close(sh_list->ad_cmd->pipe_fd[0]); // 파이프로부터 읽는 부분 닫기
					dup2(sh_list->ad_cmd->pipe_fd[1], STDOUT_FILENO);
					close(sh_list->ad_cmd->pipe_fd[1]);
				}
				
				// [명령어 실행]
				if (is_builtin(curr_cmd->con))
					execute_builtin(sh_list, curr_cmd, envp);
				else
					execute_external(curr_cmd, envp);

				exit(EXIT_FAILURE); // [자식 프로세스 종료]
			}
			else // [부모 프로세스]
			{
				// [이전 파이프 출력 닫기]
				if (pre_fd != -1)
					close(pre_fd);
				
				// [현재 파이프를 (다음 명령어를 위해) 유지]
				if (curr_cmd->next && curr_cmd->next->type == N_PIP)
				{
					close(sh_list->ad_cmd->pipe_fd[1]); // 파이프 쓰기 닫기
					pre_fd = sh_list->ad_cmd->pipe_fd[0]; // 읽기 부분 유지
				}
				else
					pre_fd = -1; // 다음 파이프가 없으면 초기화
			}
			curr_cmd = curr_cmd->next; // [다음 명령어로 이동]
		}
	}
	// [모든 자식 프로세스 대기]
	while (wait(&status) > 0);
}