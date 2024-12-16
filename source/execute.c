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
void    here_is_redirection(t_adcmd *adcmd, int *file)
{
    //t_adcmd *current;
    //current = adcmd;
    if (adcmd->redlist[0]->type == N_RED_IN)
        *file = open(adcmd->redlist[0]->file_name, O_RDONLY);
    else if (adcmd->redlist[0]->type == N_RED_OUT)
        *file = open(adcmd->redlist[0]->file_name, O_CREAT | O_RDONLY | O_TRUNC, 0644);
    if (*file == -1)
         print_error_and_exit("redirection is error");

}

////////////////////////////////////////////////////////////////////////////////
void extreme_mini_execve(t_adcmd *adcmd, char **envp)
{
    char *path;
    int file;

    if (adcmd->redlist)
        here_is_redirection(adcmd, &file);

    path = find_command_path(adcmd, envp);
    if (!path)
    {
        fprintf(stderr, "minishell: command not found: %s\n", adcmd->argv[0]);
        exit(1);
    }
    if (adcmd->pipe_fd[0] != -1)
        close(adcmd->pipe_fd[0]);  // 읽기 끝 닫기
    dup2(file, 0);
    if (adcmd->pipe_fd[1] != -1)
    {
        dup2(adcmd->pipe_fd[1], STDOUT_FILENO);  // 파이프 쓰기를 표준 출력으로
        close(adcmd->pipe_fd[1]);  // 원본 파이프 쓰기 닫기
    }
    close(file);
    // close(adcmd->pipe_fd[0]);
	// dup2(adcmd->pipe_fd[1], 1);
	// close(adcmd->pipe_fd[1]);
	
    if (execve(path, adcmd->argv, envp) == -1)  // envp 전달
    {
        perror("execve");
        free(path);
        exit(1);
    }
}

void extreme_mini_execve2(t_adcmd *adcmd, char **envp)
{
    char *path;

    int file;
    if (adcmd->redlist)
        here_is_redirection(adcmd, &file);
    path = find_command_path(adcmd, envp);
    if (!path)
    {
        fprintf(stderr, "minishell: command not found: %s\n", adcmd->argv[0]);
        exit(1);
    }
    if (adcmd->prev && adcmd->prev->pipe_fd[1] != -1)
        close(adcmd->prev->pipe_fd[1]);  // 이전 파이프의 쓰기 끝 닫기
    dup2(file, 1);
    if (adcmd->prev && adcmd->prev->pipe_fd[0] != -1)
    {
        dup2(adcmd->prev->pipe_fd[0], 0);  // 이전 파이프 읽기를 표준 입력으로
        close(adcmd->prev->pipe_fd[0]);  // 원본 파이프 읽기 닫기
    }
    close(file);
	// close(adcmd->pipe_fd[1]);
	// dup2(adcmd->pipe_fd[0], 0);
	// close(adcmd->pipe_fd[0]);
    if (execve(path, adcmd->argv, NULL) == -1)
    {
        perror("execve");
        free(path);
        exit(1);
    }
}
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
        {
            file = open(cmd->redlist[i]->file_name, O_RDONLY);
            if (file == -1)
            {
                perror("redirection");
                exit(1);
            }
            dup2(file, STDIN_FILENO);
            close(file);
        }
        else if (cmd->redlist[i]->type == N_RED_OUT)
        {
            file = open(cmd->redlist[i]->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (file == -1)
            {
                perror("redirection");
                exit(1);
            }
            dup2(file, STDOUT_FILENO);
            close(file);
        }
        else if (cmd->redlist[i]->type == N_RED_OUT_AP)
        {
            file = open(cmd->redlist[i]->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (file == -1)
            {
                perror("redirection");
                exit(1);
            }
            dup2(file, STDOUT_FILENO);
            close(file);
        }
        i++;
    }
    // 파이프 입력 처리 (이전 명령어에서 입력 받기)
    if (cmd->prev && cmd->prev->pipe_fd[0] != -1)
    {
        dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
        close(cmd->prev->pipe_fd[0]);
    }
    // 파이프 출력 처리 (다음 명령어로 출력 보내기)
    if (cmd->next && cmd->pipe_fd[1] != -1)
    {
        dup2(cmd->pipe_fd[1], STDOUT_FILENO);
        close(cmd->pipe_fd[1]);
    }
    // 모든 파이프 디스크립터 닫기
    t_adcmd *tmp = cmd;
    while (tmp)
    {
        if (tmp->pipe_fd[0] != -1)
            close(tmp->pipe_fd[0]);
        if (tmp->pipe_fd[1] != -1)
            close(tmp->pipe_fd[1]);
        tmp = tmp->next;
    }
    tmp = cmd;
    while (tmp)
    {
        if (tmp->pipe_fd[0] != -1)
            close(tmp->pipe_fd[0]);
        if (tmp->pipe_fd[1] != -1)
            close(tmp->pipe_fd[1]);
        tmp = tmp->prev;
    }

    path = find_command_path(cmd, envp);
    if (!path)
    {
        fprintf(stderr, "minishell: command not found: %s\n", cmd->argv[0]);
        free_adcmd(cmd);
        exit(1);
    }
    execve(path, cmd->argv, envp);
    free(path);
    free_adcmd(cmd);
    perror("execve");
    exit(1);
}

void execute(t_sh *sh_list, char **envp)
{
    t_adcmd *current;
    t_adcmd *temp;
    int status;

    if (!sh_list || !sh_list->ad_cmd)
        return;

    current = sh_list->ad_cmd;
    while (current != NULL)
    {
        if (current->next)
        {
            if (pipe(current->pipe_fd) < 0)
                print_error_and_exit("pipe error");
        }
        else
        {
            current->pipe_fd[0] = -1;
            current->pipe_fd[1] = -1;
        }

        current->pid = fork();
        if (current->pid == -1)
        {
            perror("fork");
            // 에러 발생 시 파이프 정리
            temp = sh_list->ad_cmd;
            while (temp != NULL)
            {
                if (temp->pipe_fd[0] != -1)
                    close(temp->pipe_fd[0]);
                if (temp->pipe_fd[1] != -1)
                    close(temp->pipe_fd[1]);
                temp = temp->next;
            }
            return;
        }
        if (current->pid == 0)
        {
            execute_command(current, envp);
        }
        else
        {
            // 현재 명령어의 write 엔드와 이전 명령어의 read 엔드를 닫음
            if (current->pipe_fd[1] != -1)
                close(current->pipe_fd[1]);
            if (current->prev && current->prev->pipe_fd[0] != -1)
                close(current->prev->pipe_fd[0]);
        }
        current = current->next;
    }
    // 남은 파이프 닫기
    current = sh_list->ad_cmd;
    while (current != NULL)
    {
        if (current->pipe_fd[0] != -1)
            close(current->pipe_fd[0]);
        if (current->pipe_fd[1] != -1)
            close(current->pipe_fd[1]);
        current = current->next;
    }
    // 모든 자식 프로세스 대기
    current = sh_list->ad_cmd;
    while (current != NULL)
    {
        waitpid(current->pid, &status, 0);
        if (WIFEXITED(status))
            current->exit_code = WEXITSTATUS(status);
        current = current->next;
    }
}