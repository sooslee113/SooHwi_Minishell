#include "../include/minishell.h"

int count_redirections(t_cmd *head_cmd) 
{
    int count;
    t_cmd *temp_cmd;

    count = 0;
    temp_cmd = head_cmd;
    while (temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0) 
    {
        if (temp_cmd->type == N_RED_OUT || temp_cmd->type == N_RED_OUT_AP ||
            temp_cmd->type == N_RED_IN || temp_cmd->type == N_RED_HRDC) 
        {
            count++;
        }
        temp_cmd = temp_cmd->next;
    }
    return (count);
}

int    making_argv(t_cmd *head_cmd)
{
    int count;
    t_cmd *temp_cmd;

    temp_cmd = head_cmd;
    count = 0;
    while(temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0)
    {
        if (temp_cmd->type == N_WORD)
        {
            if (temp_cmd -> con)
            count ++;
        }
        temp_cmd = temp_cmd -> next;
    }
    return (count);
}

void	init_ad_cmd(t_adcmd *ad_cmd)
{
    ad_cmd->argv = NULL; // 명령어 인자 배열 초기화
    ad_cmd->type = 0; // 타입 초기화 (0 또는 기본값으로 설정)
    ad_cmd->pipe_fd[0] = -1; // 파이프 초기화
    ad_cmd->pipe_fd[1] = -1;
    ad_cmd->pid = -1; // 프로세스 ID 초기화
    ad_cmd->redlist = NULL; // 리다이렉션 리스트 초기화
    ad_cmd->redlist_count = 0; // 리다이렉션 개수 초기화
    ad_cmd->exit_code = 0; // 종료 코드 초기화
    ad_cmd->next = NULL; // 다음 노드 초기화
    ad_cmd->prev = NULL; // 이전 노드 초기화
}

t_cmd *populate_redlist(t_adcmd *ad_cmd, t_cmd *head_cmd) 
{
    int redlist_count;
    t_cmd *temp_cmd;
    int i;

    redlist_count = count_redirections(head_cmd);
    ad_cmd->redlist = safe_malloc(sizeof(t_redlist *) * redlist_count);
    ad_cmd->redlist_count = redlist_count;

    temp_cmd = head_cmd;
    i = 0;

    while (temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0) 
    {
        if (temp_cmd->type == N_RED_OUT || temp_cmd->type == N_RED_OUT_AP ||
            temp_cmd->type == N_RED_IN || temp_cmd->type == N_RED_HRDC) {
            ad_cmd->redlist[i] = safe_malloc(sizeof(t_redlist));
            ad_cmd->redlist[i]->type = temp_cmd->type;
            // 다음 노드가 파일 이름인지 확인 후 복사
            if (temp_cmd->next && temp_cmd->next->con) 
            {
                ad_cmd->redlist[i]->file_name = ft_strdup(temp_cmd->next->con);
            } 
            else 
            {
                ad_cmd->redlist[i]->file_name = NULL;
            }

            i++;
            // 리다이렉션 토큰 및 파일 이름 건너뛰기
            temp_cmd = temp_cmd->next;
        }
        temp_cmd = temp_cmd->next;
    }
    return temp_cmd; // 리다이렉션 처리 후의 명령어 위치 반환
}


void real_making_argv(t_sh *sh_list, t_cmd *head_cmd) 
{
    int one_dim;
    t_cmd *temp_cmd;
    int i;
    t_adcmd *curr_adcmd;

    temp_cmd = head_cmd;
    curr_adcmd = sh_list->ad_cmd;
    while (curr_adcmd->next)  // 마지막 노드로 이동
        curr_adcmd = curr_adcmd->next;

    one_dim = making_argv(temp_cmd);
    curr_adcmd->argv = safe_malloc(sizeof(char *) * (one_dim + 1));
    i = 0;

    while (temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0 && i < one_dim) 
    {
        if (temp_cmd->type == N_WORD) 
        {
            curr_adcmd->argv[i] = ft_strdup(temp_cmd->con);
            i++;
        }
        else if (temp_cmd->type == N_RED_OUT || temp_cmd->type == N_RED_OUT_AP ||
                 temp_cmd->type == N_RED_IN || temp_cmd->type == N_RED_HRDC) 
        {
            temp_cmd = temp_cmd->next;
            while (temp_cmd && temp_cmd->type != N_WORD) 
                temp_cmd = temp_cmd->next;

            if (temp_cmd && temp_cmd->type == N_WORD) 
            {
                curr_adcmd->argv[i] = ft_strdup(temp_cmd->con);
                i++;
            }
        }
        temp_cmd = temp_cmd->next;
    }
    curr_adcmd->argv[i] = NULL;
}


int is_in_redlist(t_adcmd *ad_cmd, char *arg)
{
    int k = 0;

    while (k < ad_cmd->redlist_count)
    {
        if (ad_cmd->redlist[k]->file_name &&
            ft_strcmp(arg, ad_cmd->redlist[k]->file_name) == 0)
        {
            return 1; // redlist에 존재함
        }
        k++;
    }
    return 0; // redlist에 존재하지 않음
}
void free_old_argv(char **argv)
{
    int i = 0;

    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}
char **create_new_argv(t_adcmd *ad_cmd)
{
    int new_size;
    int i; 
    int j;
    char **new_argv;

    new_size = 0;
    i = 0;
    j = 0;
    // 기존 argv의 크기 측정
    while (ad_cmd->argv[new_size])
        new_size++;

    new_argv = safe_malloc(sizeof(char *) * (new_size + 1)); // NULL 포함 크기
    i = 0;
    while (ad_cmd->argv[i])
    {
        if (!is_in_redlist(ad_cmd, ad_cmd->argv[i])) // redlist에 없으면 추가
        {
            new_argv[j] = ft_strdup(ad_cmd->argv[i]);
            j++;
        }
        i++;
    }
    new_argv[j] = NULL; // NULL로 종료
    return new_argv;
}



void remove_file_name_from_argv(t_adcmd *ad_cmd)
{
    if (!ad_cmd || !ad_cmd->argv || !ad_cmd->redlist)
        return;

    char **new_argv;
    new_argv = create_new_argv(ad_cmd);
    free_old_argv(ad_cmd->argv);
    ad_cmd->argv = new_argv;
}


void fill_in_adcmd(t_sh *sh_list, t_cmd *head_cmd)
{
    t_cmd *curr_cmd;
    t_adcmd *curr_adcmd;
    t_adcmd *prev_adcmd;

    if (!sh_list || !head_cmd)
        return;

    // 첫 번째 노드 생성
    sh_list->ad_cmd = safe_malloc(sizeof(t_adcmd));
    init_ad_cmd(sh_list->ad_cmd);
    curr_adcmd = sh_list->ad_cmd;
    prev_adcmd = NULL;
    curr_cmd = head_cmd;

    while (curr_cmd)
    {
        // 현재 명령어 블록 처리
        real_making_argv(sh_list, curr_cmd);
        curr_cmd = populate_redlist(curr_adcmd, curr_cmd);
        remove_file_name_from_argv(curr_adcmd);

        // 파이프를 만나면 새로운 노드 생성
        if (curr_cmd && ft_strncmp(curr_cmd->con, "|", 1) == 0)
        {
            // 파이프 카운트 증가
            sh_list->pipe_cnt++;
            // 다음 노드 생성
            curr_adcmd->next = safe_malloc(sizeof(t_adcmd));
            prev_adcmd = curr_adcmd;
            curr_adcmd = curr_adcmd->next;
            init_ad_cmd(curr_adcmd);
            curr_adcmd->prev = prev_adcmd;
            // 파이프 다음 명령어로 이동
            if (curr_cmd->next)
                curr_cmd = curr_cmd->next;
            else
                break;
        }
        else
        {
            break; // 더 이상 처리할 명령어가 없음
        }
    }
}

