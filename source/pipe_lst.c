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
    return count;
}

int making_argv_count(t_cmd *head_cmd)
{
    int count;
    t_cmd *temp_cmd;

    count = 0;
    temp_cmd = head_cmd;

    while (temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0)
    {
        if (temp_cmd->type == N_WORD && temp_cmd->con)
        {
            count++;
        }
        temp_cmd = temp_cmd->next;
    }
    return count;
}

void init_ad_cmd(t_adcmd *ad_cmd)
{
    ad_cmd->argv = NULL;
    ad_cmd->type = 0;
    ad_cmd->pid = -1;
    ad_cmd->redlist = NULL;
    ad_cmd->redlist_count = 0;
    ad_cmd->exit_code = 0;
    ad_cmd->next = NULL;
    ad_cmd->prev = NULL;
}

static void allocate_redlist_memory(t_adcmd *ad_cmd, int redlist_count)
{
    ad_cmd->redlist = safe_malloc(sizeof(t_redlist *) * redlist_count);
    ad_cmd->redlist_count = redlist_count;
}

static void process_redirection(t_adcmd *ad_cmd, t_cmd *temp_cmd, int *index)
{
    t_redlist *new_red;

    new_red = safe_malloc(sizeof(t_redlist));
    new_red->type = temp_cmd->type;

    if (temp_cmd->next && temp_cmd->next->con)
    {
        new_red->file_name = ft_strdup(temp_cmd->next->con);
    }
    else
    {
        new_red->file_name = NULL;
    }

    ad_cmd->redlist[*index] = new_red;
    (*index)++;
}

t_cmd *populate_redlist(t_adcmd *ad_cmd, t_cmd *head_cmd) 
{
    int redlist_count;
    t_cmd *temp_cmd;
    int i;

    redlist_count = count_redirections(head_cmd);
    temp_cmd = head_cmd;
    i = 0;
    allocate_redlist_memory(ad_cmd, redlist_count);
    while (temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0) 
    {
        if (temp_cmd->type == N_RED_OUT || temp_cmd->type == N_RED_OUT_AP ||\
            temp_cmd->type == N_RED_IN || temp_cmd->type == N_RED_HRDC) 
        {
            process_redirection(ad_cmd, temp_cmd, &i);
            temp_cmd = temp_cmd->next; // Skip the redirection file name
        }
        temp_cmd = temp_cmd->next;
    }
    return temp_cmd;
}

void fill_in_argv(t_adcmd *ad_cmd, t_cmd *head_cmd)
{
    int count;
    t_cmd *temp_cmd;
    int i;

    count = making_argv_count(head_cmd);
    temp_cmd = head_cmd;
    i = 0;

    ad_cmd->argv = safe_malloc(sizeof(char *) * (count + 1));

    while (temp_cmd && ft_strncmp(temp_cmd->con, "|", 1) != 0 && i < count)
    {
        if (temp_cmd->type == N_WORD)
        {
            ad_cmd->argv[i] = ft_strdup(temp_cmd->con);
            i++;
        }
        temp_cmd = temp_cmd->next;
    }
    ad_cmd->argv[i] = NULL;
}

int is_in_redlist(t_adcmd *ad_cmd, char *arg)
{
    int i;

    i = 0;
    while (i < ad_cmd->redlist_count)
    {
        if (ad_cmd->redlist[i]->file_name &&
            ft_strcmp(arg, ad_cmd->redlist[i]->file_name) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
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

    while (ad_cmd->argv[new_size])
        new_size++;

    new_argv = safe_malloc(sizeof(char *) * (new_size + 1));

    while (ad_cmd->argv[i])
    {
        if (!is_in_redlist(ad_cmd, ad_cmd->argv[i]))
        {
            new_argv[j] = ft_strdup(ad_cmd->argv[i]);
            j++;
        }
        i++;
    }
    new_argv[j] = NULL;
    return new_argv;
}

void remove_file_name_from_argv(t_adcmd *ad_cmd)
{
    char **new_argv;

    if (!ad_cmd || !ad_cmd->argv || !ad_cmd->redlist)
        return;

    new_argv = create_new_argv(ad_cmd);
    free_old_argv(ad_cmd->argv);
    ad_cmd->argv = new_argv;
}

static t_adcmd *create_new_adcmd(t_adcmd **prev_adcmd)
{
    t_adcmd *new_adcmd;

    new_adcmd = safe_malloc(sizeof(t_adcmd));
    init_ad_cmd(new_adcmd);
    if (*prev_adcmd)
    {
        (*prev_adcmd)->next = new_adcmd;
        new_adcmd->prev = *prev_adcmd;
    }
    *prev_adcmd = new_adcmd;
    return new_adcmd;
}

void fill_in_adcmd(t_sh *sh_list, t_cmd *head_cmd)
{
    t_cmd *curr_cmd;
    t_adcmd *curr_adcmd;
    t_adcmd *prev_adcmd;

    curr_cmd = head_cmd;
    prev_adcmd = NULL;
    curr_adcmd = create_new_adcmd(&prev_adcmd);
    sh_list->ad_cmd = curr_adcmd;

    while (curr_cmd)
    {
        fill_in_argv(curr_adcmd, curr_cmd);
        curr_cmd = populate_redlist(curr_adcmd, curr_cmd);
        remove_file_name_from_argv(curr_adcmd);

        if (curr_cmd && ft_strncmp(curr_cmd->con, "|", 1) == 0)
        {
            sh_list->pipe_cnt++;
            curr_cmd = curr_cmd->next;
            curr_adcmd = create_new_adcmd(&prev_adcmd);
        }
    }
}
