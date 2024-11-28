/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/28 21:25:09 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_sh_list(t_sh *sh_list)
{
	sh_list->export_head = NULL;
	sh_list->pipe_cnt = 0;
	// 필요한 멤버 추가 초기화
}

void lets_free(char **str)
{
    int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}


// echo 명령어 makefile에 넣는 법이 어려워 여기 다 넣습니다.
void echo_out(t_cmd *cmd)
{
    char **temp;

    while (cmd)
    {
        temp = ft_split(cmd->con, ' '); // 공백으로 split
        if (!temp)
            return;

        write(1, temp[0], strlen(temp[0])); // 첫 번째 단어 출력
        if (cmd->next)                      // 다음 명령어가 있다면 공백 추가
            write(1, " ", 1);

        lets_free(temp); // split 결과 해제
        cmd = cmd->next; // 다음 명령어로 이동
    }
}

void ft_echo(t_cmd *cmd)
{
    int flag_n = 0;

    // 첫 번째 명령어가 `-n`인지 확인
    if (cmd && strcmp(cmd->con, "-n") == 0)
    {
        flag_n = 1;
        cmd = cmd->next; // `-n`을 건너뛰고 다음 명령어로
    }

    echo_out(cmd); // 나머지 명령어 출력

    if (!flag_n) // `-n`이 없으면 줄바꿈
        write(1, "\n", 1);
}
// 여기까지가 echo

// 이건 env
void	print_export_list(t_export *export_head)
{
	t_export *temp = export_head;

	while (temp != NULL)
	{
		if (temp->value != NULL)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
// 여기까지가 env

// 여기 부터는 export
void new_key_value_parsing(char *str, char **t_key, char **t_value)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == '=')
        {
            *t_key = ft_substr(str, 0, i); 
            *t_value = ft_substr(str, i + 1, ft_strlen(str) - i - 1); 
            return;
        }
        i++;
    }
    *t_key = ft_strdup(str);
    *t_value = NULL; // 값이 없는 경우 NULL
}

int export_edgecase(char *key)
{
    int i = 0;

    if (!key)
        return (0);
    if (key[0] != '_' && ft_isalpha(key[0]) == 0)
        return (0); // 잘못된 시작 문자

    while (key[i])
    {
        if (ft_isalnum(key[i]) == 0 && key[i] != '_')
            return (0); // 유효하지 않은 문자
        i++;
    }
    return (1);
}

void add_export_list2(t_export **p_export, char *t_key, char *t_value)
{
    t_export *new_node;
    t_export *temp_head = *p_export;

    // 기존 키 업데이트 처리
    while (temp_head != NULL)
    {
        if (ft_strcmp(temp_head->key, t_key) == 0)
        {
            if (t_value != NULL)
            {
                if (temp_head->value != NULL)
                    free(temp_head->value);
                temp_head->value = ft_strdup(t_value);
            }
            return;
        }
        temp_head = temp_head->next;
    }

    // 새로운 노드 추가
    new_node = malloc(sizeof(t_export));
    if (!new_node)
        exit(1);
    new_node->key = ft_strdup(t_key);
    new_node->value = (t_value != NULL) ? ft_strdup(t_value) : NULL;
    new_node->next = NULL;

    if (*p_export == NULL)
        *p_export = new_node;
    else
    {
        temp_head = *p_export;
        while (temp_head->next != NULL)
            temp_head = temp_head->next;
        temp_head->next = new_node;
    }
}

void divde_key_value(char *arg, t_sh *p_sh_list)
{
    char *t_key;
    char *t_value;

    new_key_value_parsing(arg, &t_key, &t_value);
    if (!export_edgecase(t_key)) // 키 유효성 검사
    {
        printf("Invalid KEY: %s\n", t_key);
        free(t_key); // 메모리 누수 방지
        free(t_value);
        return;
    }
    add_export_list2(&(p_sh_list->export_head), t_key, t_value);
    free(t_key);  // 메모리 해제
    free(t_value);
}

void insert_envp(t_cmd *cmd_node, t_sh *p_sh_list)
{
    while (cmd_node)
    {
        divde_key_value(cmd_node->con, p_sh_list);
        cmd_node = cmd_node->next;
    }
}

void free_temp(t_export *sorted_list)
{
    t_export *temp;
    while (sorted_list)
    {
        temp = sorted_list->next;
        free(sorted_list->key);
        if (sorted_list->value != NULL)
            free(sorted_list->value);
        free(sorted_list);
        sorted_list = temp;
    }
}

void list_copy(t_export **sorted_list, t_export *temp)
{
    while (temp)
    {
        t_export *new_node = malloc(sizeof(t_export));
        if (!new_node)
            exit(1);
        new_node->key = ft_strdup(temp->key);
        new_node->value = (temp->value != NULL) ? ft_strdup(temp->value) : NULL;
        new_node->next = *sorted_list;
        *sorted_list = new_node;
        temp = temp->next;
    }
}

void print_export_list2(t_export *export_head)
{
    t_export *sorted_list = NULL;
    t_export *temp = export_head;

    list_copy(&sorted_list, temp); // 리스트 복사
    envp_sort(&sorted_list);      // 복사본 정렬

    temp = sorted_list;
    while (temp != NULL)
    {
        if (temp->value != NULL)
            printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
        else
            printf("declare -x %s\n", temp->key);
        temp = temp->next;
    }
    free_temp(sorted_list); // 복사본 메모리 해제
}
// 여기 까지 export

// 여기서 부터는 unset

void removeNodeValue(t_sh *sh_list, char *target)
{
    t_export *del_node;
    t_export *prev_node;

    if (sh_list->export_head == NULL)
        return;

    // 첫 번째 노드를 처리
    if (ft_strncmp(sh_list->export_head->key, target, ft_strlen(target)) == 0)
    {
        del_node = sh_list->export_head;
        sh_list->export_head = sh_list->export_head->next;
        free(del_node->key);
        if (del_node->value)
            free(del_node->value);
        free(del_node);
        printf("Removed node with key: %s\n", target); // 삭제된 노드 확인
        return;
    }

    // 이후 노드를 처리
    prev_node = sh_list->export_head;
    del_node = sh_list->export_head->next;
    while (del_node != NULL)
    {
        if (ft_strncmp(del_node->key, target, ft_strlen(target)) == 0)
        {
            prev_node->next = del_node->next;
            free(del_node->key);
            if (del_node->value)
                free(del_node->value);
            free(del_node);
            printf("Removed node with key: %s\n", target); // 삭제된 노드 확인
            return;
        }
        prev_node = del_node;
        del_node = del_node->next;
    }
}

void working_unset(t_sh *sh_list, char *cmd)
{
    char **ept_temp;
    int i;

    ept_temp = ft_split(cmd, ' ');
    if (ept_temp == NULL)
    {
        printf("Error: ft_split failed\n");
        return;
    }
    /* 디버깅용*/
        i = 0;
    while(ept_temp[i])
    {
        printf("ept_temp[%d] = %s ", i,ept_temp[i]);
        i ++;
    }
    /* 여기까지 */
    i = 0; // ept_temp에는 삭제할 키 값이 있다.
    while (ept_temp[i]) // `ept_temp[0]`부터 시작하여 처리
    {
        printf("Unset target: %s\n", ept_temp[i]); // unset 명령어 뒤에 인자 출력
        removeNodeValue(sh_list, ept_temp[i]); // 해당 키를 export list에서 삭제
        i++;
    }

    // ept_temp 메모리 해제
    i = 0;
    while (ept_temp[i])
    {
        free(ept_temp[i]);
        i++;
    }
    free(ept_temp);
}
// 여기 까지가 unset

// 여기 부터 pwd
void	ft_pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("getcwd");
        return ;
    }
    return ;
}
// 여기 까지가 pwd

// 여기서부터 pipe
void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (NULL == ret)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

void free_pipe(t_pipe *pipe)
{
    t_pipe *temp;

    while (pipe != NULL)
    {
        temp = pipe->next;

        free(pipe->fd);
        if (pipe->redlist)
        {
            free(pipe->redlist->type);
            free(pipe->redlist->file_name);
            free(pipe->redlist);
        }

        free(pipe);
        pipe = temp;
    }
}

void init_pipe(t_pipe **pipe)   
{
    *pipe = safe_malloc(sizeof(t_pipe));
    (*pipe)->argv = NULL;
    (*pipe)->exit_code = 1;
    (*pipe)->fd = safe_malloc(sizeof(int) * 2);
    (*pipe)->pid = 0;
    (*pipe)->redlist = safe_malloc(sizeof(t_redlist));
    (*pipe)->redlist->type = NULL;
    (*pipe)->redlist->file_name = NULL;
    (*pipe)->next = NULL;
    (*pipe)->prev = NULL;
}

t_pipe *create_pipe_node(t_pipe **pipe_line, t_pipe *current_pipe)
{
    t_pipe *new_pipe;

    init_pipe(&new_pipe); // 새 파이프 노드 초기화

    if (*pipe_line == NULL) // 처음 생성되는 노드일 경우
    {
        *pipe_line = new_pipe;
        return *pipe_line;
    }
    else // 기존 노드가 있을 경우 연결
    {
        current_pipe->next = new_pipe;
        new_pipe->prev = current_pipe;
        return new_pipe;
    }
}

int count_cmd_segment(t_cmd *cmd)
{
    int count;
    
    count = 0;
    while (cmd != NULL && ft_strncmp(cmd->con, "|", 1) != 0)
    {
        count++;
        cmd = cmd->next;
    }

    return count;
}

t_type set_type2(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return N_PIP;
	else if (ft_strcmp(token, "||") == 0)
		return N_PIPS;
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<>") == 0)
		return N_RED_OUT;
	else if (ft_strcmp(token, ">>") == 0)
		return N_RED_OUT_AP;
	else if (ft_strcmp(token, "<") == 0)
		return N_RED_IN;
	else if (ft_strcmp(token, "<<") == 0)
		return N_RED_HRDC;
	else if (ft_strcmp(token, ";") == 0)
		return N_SEMIC;
	else if (ft_strcmp(token, ";;") == 0)
		return N_SEMICS;
	else
		return N_WORD;
}
void fill_pipe_argv(t_pipe *current_pipe, t_cmd **cmd)
{
    int i = 0;
    t_cmd *temp_cmd = *cmd;

    while (temp_cmd != NULL && ft_strncmp(temp_cmd->con, "|", 1) != 0)
    {
        current_pipe->argv[i] = ft_strdup(temp_cmd->con); // 명령어 복사
        temp_cmd = temp_cmd->next;
        i++;
    }
    current_pipe->argv[i] = NULL; // argv의 마지막 요소 NULL
    current_pipe->type = set_type2(current_pipe->argv[0]);
    *cmd = temp_cmd; // 현재 명령어 위치를 업데이트
}
t_pipe *fill_in_pipe(t_cmd *cmd, t_pipe *pipe_line)
{
    t_cmd *temp_cmd;
    t_pipe *current_pipe = NULL;
    int count;

    count = 0;
    temp_cmd = cmd;
    // 파이프 블록 처리
    while (temp_cmd != NULL)
    {
        // 새 t_pipe 노드 초기화
        current_pipe = create_pipe_node(&pipe_line, current_pipe);
        // 현재 파이프 세그먼트 크기 계산
        count = count_cmd_segment(temp_cmd);
        // argv 메모리 할당
        current_pipe->argv = safe_malloc(sizeof(char *) * (count + 1));
        // argv에 명령어 및 인자 복사
         fill_pipe_argv(current_pipe, &temp_cmd);
        // 파이프 세그먼트가 끝난 경우, 다음으로 이동
        if (temp_cmd != NULL && ft_strncmp(temp_cmd->con, "|", 1) == 0)
            temp_cmd = temp_cmd->next;
    }

    return pipe_line;
}
// 여기 까지가 pipe
int	main(int ac, char** av, char **envp)
{
	t_sh 	sh_list;
	t_cmd	*head_cmd;
    t_pipe  *pipe_line;
	char	*input;

	(void)ac;
	(void)av;
	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);
	sig_handle(&sh_list);
    pipe_line = NULL;
    //init_pipe(&pipe_line);
	while(1)
	{
		input = readline("minishell$ ");
		if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
			break;
		if(*input)
			add_history(input);
		head_cmd = tokenize_input(input, &sh_list);//head_cmd에는 모든 명령어 각각이 t_cmd형태로 토크나이징 및 타입이 지정되어 있음.
        pipe_line = fill_in_pipe(head_cmd, pipe_line);
		t_cmd *curr_cmd = head_cmd;//테스트 코드
		for (;curr_cmd != NULL; curr_cmd = curr_cmd->next) ////////////////
        {
			printf("cmd : %s / type : %d\n", curr_cmd->con, curr_cmd->type); //////////////////
        }

        //execute(&sh_list, temp, envp);
		free(input);
	}
	printf("The End!\n");
	return (0);
}


/*
테스트 케이스
	//execute(&sh_list, head_cmd, envp);
		//echo 테스트
		// if (head_cmd && ft_strncmp(head_cmd->con, "echo", 4) == 0)
        // {
        //     ft_echo(head_cmd->next); // "echo" 이후의 명령어를 처리
        // }
		// else if (head_cmd && ft_strncmp(head_cmd->con, "env", 3) == 0) //env테스트
		// {
		// 	print_export_list(sh_list.export_head); // 환경 변수 출력
		// }
		// else if (head_cmd && ft_strncmp(head_cmd->con, "export", 6) == 0) // export 테스트
		// {
    	// 	if (head_cmd->next == NULL)
        // 		print_export_list2(sh_list.export_head); // export만 입력한 경우
    	// 	else
        // 		insert_envp(head_cmd->next, &sh_list); // key=value 입력 처리
		// }
        // else if (head_cmd && ft_strncmp(head_cmd->con, "unset", 5) == 0)
        // {
        //     if (head_cmd->next)
        //     {  // unset 명령어 뒤에 값이 있을 때만 처리
        //         while(head_cmd->next != NULL)
        //         {
        //             working_unset(&sh_list, head_cmd->next->con);
        //             head_cmd = head_cmd -> next;
        //         }
        //     } // unset 명령어 처리
        // }
		// else if (head_cmd && ft_strncmp(head_cmd->con, "pwd", 3) == 0)
		// {
		// 	ft_pwd(); // 현재 디렉토리 출력
		// }
*/

        // // 파이프 확인용 디버깅
		// t_pipe *temp = pipe_line;
        // while (temp != NULL)
        // {
        //     printf("Pipe command:\n");
        //     for (int i = 0; temp->argv[i] != NULL; i++)
        //     {
        //         printf("- %s\n", temp->argv[i]);
        //         printf("%d", temp->type);
        //     }
        //     temp = temp->next;
        // }