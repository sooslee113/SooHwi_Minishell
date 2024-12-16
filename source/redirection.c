#include "../include/minishell.h"

void	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe for heredoc");
		exit(EXIT_FAILURE);
	}

	// Here-doc 입력 받기
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipe_fd[1]); // 쓰기 종료

	// Here-doc 내용을 표준 입력으로 연결
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]); // 읽기 종료
}


void	handle_redirection(t_cmd **cmd)
{
	int		fd;

	while (*cmd && ((*cmd)->type == N_RED_OUT\
		|| (*cmd)->type == N_RED_OUT_AP || (*cmd)->type == N_RED_IN\
		|| (*cmd)->type == N_RED_HRDC))
	{
		if ((*cmd)->type == N_RED_OUT || (*cmd)->type == N_RED_OUT_AP) // '>' , '>>'
		{
			if ((*cmd)->type == N_RED_OUT)
				fd = open((*cmd)->next->con, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open((*cmd)->next->con, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				exit(1);//error 처리 따로 
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if ((*cmd)->type == N_RED_IN) // '<'
		{
			fd = open((*cmd)->next->con, O_RDONLY);
			if (fd < 0)
				exit(1);//error 처리 따로 
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if ((*cmd)->type == N_RED_HRDC) // '<<'
			handle_heredoc((*cmd)->next->con);
		// 리다이렉션 노드와 해당 파일 이름 노드를 스킵
		*cmd = (*cmd)->next->next;
	}
}
