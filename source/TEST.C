/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:11:28 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/27 16:58:03 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_pipex *pipex)
{
	pipex->pid1 = 0;
	pipex->pid2 = 0;
	pipex->file1 = 0;
	pipex->file2 = 0;
	pipex->fd[0] = 0;
	pipex->fd[1] = 0;
	pipex->path = NULL;
	pipex->cmd1_part = NULL;
	pipex->cmd2_part = NULL;
	pipex->path_cmd1 = NULL;
	pipex->path_cmd2 = NULL;
}

void	set_pipe(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->pid1 == 0)// 자식프로세스면?
	{
		int	file1 = open(av[1], O_RDONLY);// 1번파일을 읽기전용으로 열기
		close(pipex->fd[0]);//파이프출구 닫기
		dup2(file1, STDIN_FILENO);//파일디스크립터에 프로세스 인풋 덮어쓰기->프로세스에 FILE1이 들어옴
		dup2(pipex->fd[1], STDOUT_FILENO);//파이프입구에 프로세스 아웃풋 덮어쓰기-> 프로세스아웃풋이 파이프 입구로 통함 
		close(pipex->fd[1]);// 파이프 기존 입구 닫기
		close(file1);
		execve(pipex->path_cmd1, pipex->cmd1_part, envp);
	}
	else// 부모프로세스면?
	{
		pipex->pid2 = fork();// 또다른 자식프로세스 생성
		if (pipex->pid2 == 0)
		{
			int	file2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);//출력할 2번파일 열기
			close(pipex->fd[1]);
			dup2(pipex->fd[0], STDIN_FILENO);
			dup2(file2, STDOUT_FILENO);
			close(pipex->fd[0]);
			close(file2);
			execve(pipex->path_cmd2, pipex->cmd2_part, envp);
		}
		else
		{
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			waitpid(pipex->pid2, NULL, 0);
			waitpid(pipex->pid1, NULL, 0);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	ft_init(pipex);
	ft_set_envp(pipex, envp);
	pipex->cmd1_part = ft_split(av[2], ' ');
	pipex->cmd2_part = ft_split(av[3], ' ');
	check_cmd(pipex);
	pipe(pipex->fd);// PIPE생성
	pipex->pid1 = fork();// 부모/자식 프로세스 분기
	set_pipe(pipex, av, envp);
	ft_all_free(pipex);
	return (0);
}
