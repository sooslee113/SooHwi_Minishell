/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:20:30 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/28 21:28:56 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_sh *sh_list, t_pipe *head_pipe, char **envp)
{

	t_cmd	*curr_pipe;//현재 명령어 노드


	int		status;

	while (curr_pipe != NULL)
	{
		if (curr_pipe -> type == N_PIP)//파이프면?
		pipe(pipe_fd);//파이프설정
		if (curr_cmd->type == N_PIP)// '|'일때
			curr_cmd = curr_cmd->next;
		else if (curr_cmd->type == N_RED_OUT || curr_cmd->type == N_RED_OUT_AP\
			|| curr_cmd->type == N_RED_IN || curr_cmd->type == N_RED_HRDC)//리다이렉션일때
			handle_redirection(&curr_cmd);
		else//일반명령어일 경우 실행시작!
		{
			pid = fork();//여기부터 자식 프로세스 생성 및 실행
			if (pid == 0)
			{
				if (pre_fd != -1)//이전 OUT이 현재 IN으로 연결돼야 할 때
				{
					dup2(pre_fd, STDIN_FILENO);
					close(pre_fd);
				}
				if (curr_cmd->next && curr_cmd->next->type == N_PIP)
				{//현재명령어가 파이프를 통해 다음 명령어와 연결될 때 출력 연결 시작
					close(pipe_fd[0]);// 파이프로부터 읽는 쪽 닫기
					dup2(pipe_fd[1], STDOUT_FILENO);
					close(pipe_fd[1]);
				}
				if (is_builtin(curr_cmd->con))
					execute_builtin(sh_list, curr_cmd, envp);
				else
					execute_external(curr_cmd, envp);
				exit(EXIT_FAILURE);
			}
			else
			{
				close(pipe_fd[0]);
				dup2(STDOUT_FILENO, pipe_fd[1]);
				close(pipe_fd[1]);
			}
				
			if (pre_fd != -1)
				close(pre_fd);
			if (curr_cmd->next && curr_cmd->next->type == N_PIP)
			{
				close(pipe_fd[1]);
				pre_fd = pipe_fd[0];
			}
			curr_pipe = curr_cmd->next;
		}
	}
	while (wait(&status) > 0);
}

// #include "../include/minishell.h"

// void	execute(t_sh *sh_list, t_cmd *head_cmd, char **envp)
// {
// 	t_cmd	*curr_cmd;//현재 명령어 노드
// 	pid_t	pid;
// 	int		pipe_fd[2];//파이프용 fd
// 	int		prev_fd;//이전 명령어의 출력fd
// 	int		status;

// 	curr_cmd = head_cmd;
// 	while (curr_cmd != NULL)
// 	{
// 		if (curr_cmd->type == N_PIP)//파이프면?
// 			curr_cmd = curr_cmd->next;
// 		else if (curr_cmd->type == N_RED_OUT || curr_cmd->type == N_RED_OUT_AP\
// 			|| curr_cmd->type == N_RED_IN || curr_cmd->type == N_RED_HRDC)
// 			handle_redirection(&curr_cmd);
// 		else
// 		{
// 			if (curr_cmd->next && curr_cmd->next->type == N_PIP)
// 				pipe(pipe_fd);//파이프설정
// 			pid = fork();//여기부터 자식 프로세스 생성 및 실행
// 			if (pid == 0)
// 			{
// 				if (prev_fd != -1)
// 				{
// 					dup2(prev_fd, STDIN_FILENO);
// 					close(prev_fd);
// 				}
// 				if (curr_cmd->next && curr_cmd->next->type == N_PIP)//현재명령어 출력 연결
// 				{
// 					close(pipe_fd[0]);//읽기 닫기
// 					dup2(pipe_fd[1], STDOUT_FILENO);
// 					close(pipe_fd[1]);
// 				}
// 				if (is_builtin(curr_cmd->con))
// 					execute_builtin(sh_list, curr_cmd, envp);
// 				else
// 					execute_external(curr_cmd, envp);
// 				exit(EXIT_FAILURE);
// 			}
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			if (curr_cmd->next && curr_cmd->next->type == N_PIP)
// 			{
// 				close(pipe_fd[1]);
// 				prev_fd = pipe_fd[0];
// 			}
// 			curr_cmd = curr_cmd->next;
// 		}
// 	}
// 	while (wait(&status) > 0);
// }