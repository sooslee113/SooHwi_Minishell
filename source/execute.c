#include "../include/minishell.h"


char	*finding_envp(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*find_command_path(t_adcmd *adcmd, char **envp)
{
	char **envp_collec;
	char *path;
	char *temp;
	char *temp2;
	int i;

	path = finding_envp(envp);
	envp_collec = ft_split(path, ':');
	temp = ft_strjoin("/", (adcmd)->argv[0]);
	i = -1;
	while(envp_collec[++i])
	{
		temp2 = ft_strjoin(envp_collec[i], temp);
		if (access(temp2, X_OK) == -1)
			free(temp2);
		else
			return (temp2);
	}
	free(temp);
	free(path);
	free_double((void**)envp_collec);
	return (NULL);
}

void    close_dup(t_adcmd **cmd, int *file, int *i)
{
    if ((*cmd)->redlist[*i]->type == N_RED_IN)
    {
        *file = open((*cmd)->redlist[*i]->file_name, O_RDONLY);
        if (*file == -1)
            print_error_and_exit("redirection is wrong");
        dup2(*file, STDIN_FILENO);
        close(*file);
    }
    else if ((*cmd)->redlist[*i]->type == N_RED_OUT_AP)
    {
        *file = open((*cmd)->redlist[*i]->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (*file == -1)
            print_error_and_exit("redirection is wrong");
        dup2(*file, STDOUT_FILENO);
        close(* file);
    }
    else if ((*cmd)->redlist[*i]->type == N_RED_OUT)
    {
        *file = open((*cmd)->redlist[*i]->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (*file == -1)
            print_error_and_exit("redirection is wrong");
        dup2(*file, STDOUT_FILENO);
        close(*file);
    }
}

void    manage_fd(t_adcmd **cmd)
{
    t_adcmd *tmp;
    
    if ((*cmd)->prev && (*cmd)->prev->pipe_fd[0] != -1)
    {
        dup2((*cmd)->prev->pipe_fd[0], STDIN_FILENO);
        close((*cmd)->prev->pipe_fd[0]);
    }
    // 파이프 출력 처리 (다음 명령어로 출력 보내기)
    if ((*cmd)->next && (*cmd)->pipe_fd[1] != -1)
    {
        dup2((*cmd)->pipe_fd[1], STDOUT_FILENO);
        close((*cmd)->pipe_fd[1]);
    }
    
    tmp = *cmd;
    while (tmp)
    {
        if (tmp->pipe_fd[0] != -1)
            close(tmp->pipe_fd[0]);
        if (tmp->pipe_fd[1] != -1)
            close(tmp->pipe_fd[1]);
        tmp = tmp->next;
    }
}
////////////////////////////////////////////////////////////////////////////////

void execute_command(t_adcmd *cmd, char **envp)
{
    char *path;
    int file;
    int i;
    // 모든 리다이렉션 처리
    i = 0;
    while (i < cmd->redlist_count)
    {
        if (cmd->redlist[i]->type == N_RED_IN)
            close_dup(&cmd, &file, &i);
        else if (cmd->redlist[i]->type == N_RED_OUT_AP)
            close_dup(&cmd, &file, &i);
        else if (cmd->redlist[i]->type == N_RED_OUT)
            close_dup(&cmd, &file, &i);
        i++;
    }
    manage_fd(&cmd);
    path = find_command_path(cmd, envp);
    if (execve(path, cmd->argv, envp) == -1)
    {
        free(path);
        fprintf(stderr, "minishell: command not found: %s\n", cmd->argv[0]);
        exit(1);
    }
}
void    lets_install_the_pipe(t_adcmd **current)
{
    if ((*current)->next)
    {
        if (pipe((*current)->pipe_fd) < 0)
            print_error_and_exit("pipe error");
    }
    else
    {
        (*current)->pipe_fd[0] = -1;
        (*current)->pipe_fd[1] = -1;
    }
}
void    fork_fail(t_sh **sh_list, t_adcmd **temp)
{
    perror("fork");
    *temp = (*sh_list)->ad_cmd;
    while (*temp != NULL)
    {
        if ((*temp)->pipe_fd[0] != -1)
            close((*temp)->pipe_fd[0]);
        if ((*temp)->pipe_fd[1] != -1)
            close((*temp)->pipe_fd[1]);
        (*temp) = (*temp)->next;
    }
}

void    fork_sucess(t_adcmd **current, char **envp)
{
    if ((*current)->pid == 0) // 부
    {
            execute_command(*current, envp);
    }
    else
    {
            // 현재 명령어의 write 엔드와 이전 명령어의 read 엔드를 닫음
        if ((*current)->pipe_fd[1] != -1)
            close((*current)->pipe_fd[1]);
        if ((*current)->prev && (*current)->prev->pipe_fd[0] != -1)
            close((*current)->prev->pipe_fd[0]);
    }
}

void    colse_remain_pipe_and_wait_chilid(t_sh **sh_list, t_adcmd **current)
{
    int status;

    (*current) = (*sh_list)->ad_cmd;
    while ((*current) != NULL)
    {
        if ((*current)->pipe_fd[0] != -1)
            close((*current)->pipe_fd[0]);
        if ((*current)->pipe_fd[1] != -1)
            close((*current)->pipe_fd[1]);
        (*current) = (*current)->next;
    }
    // 모든 자식 프로세스 대기
    (*current) = (*sh_list)->ad_cmd;
    while ((*current) != NULL)
    {
        waitpid((*current)->pid, &status, 0);
        if (WIFEXITED(status))
            (*current)->exit_code = WEXITSTATUS(status);
        (*current) = (*current)->next;
    }
}

void execute(t_sh *sh_list, char **envp)
{
    t_adcmd *current;
    t_adcmd *temp;

    if (!sh_list || !sh_list->ad_cmd)
        return;

    current = sh_list->ad_cmd;
    while (current != NULL)
    {
        lets_install_the_pipe(&current);
        current->pid = fork();
        if (current->pid == -1)
        {
            fork_fail(&sh_list, &temp);
            return;
        }
        fork_sucess(&current, envp);    
        current = current->next;
    }
    colse_remain_pipe_and_wait_chilid(&sh_list, &current);
}
