/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:20:30 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/28 21:26:50 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_sh *sh_list, t_cmd *head_cmd, char **envp)
{
	t_cmd	*curr_cmd;//현재 명령어 노드
	pid_t	pid;
	int		pipe_fd[2];//파이프용 fd
	int		pre_fd;//이전 명령어의 출력fd
	int		status;

	pre_fd = -1;//처음 명령어는 입력이 없으니까 이렇게 지정해주기
	curr_cmd = head_cmd;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->type == N_PIP)// '|'일때
			curr_cmd = curr_cmd->next;
		else if (curr_cmd->type == N_RED_OUT || curr_cmd->type == N_RED_OUT_AP\
			|| curr_cmd->type == N_RED_IN || curr_cmd->type == N_RED_HRDC)//리다이렉션일때
			handle_redirection(&curr_cmd);
		else//일반명령어일 경우 실행시작!
		{
			if (curr_cmd->next && curr_cmd->next->type == N_PIP)
				pipe(pipe_fd);//파이프설정
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
				exit(EXIT_FAILURE);//자식프로세스 종료
			}
			else//부모
			{
				if (pre_fd != -1)//처음프로세스가 아니면
					close(pre_fd);//이전 파이프 출력 닫기
				if (curr_cmd->next && curr_cmd->next->type == N_PIP)
				{//다음 명령어를 위해 현재 파이프 유지하는 부분
					close(pipe_fd[1]);//파이프 쓰는 부분 닫기
					pre_fd = pipe_fd[0];//읽는 부분 유지
				}
				else
					pre_fd = -1;//다음 파이프 없으면 초기화
			curr_cmd = curr_cmd->next;
		}
	}
	while (wait(&status) > 0);//모든 자식프로세스가 종료될 떄 가지 계속 wait호출
}
