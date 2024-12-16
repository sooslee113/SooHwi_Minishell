#include "../include/minishell.h"

void free_old_argv(char **argv)
{
    int i;
    
    i = 0;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

void free_redlist(t_redlist **redlist, int redlist_count)
{
    int i;

    if (!redlist)
        return;
    
    for (i = 0; i < redlist_count; i++)
    {
        if (redlist[i])
        {
            // file_name 해제
            if (redlist[i]->file_name)
                free(redlist[i]->file_name);
            // redlist 요소 구조체 해제
            free(redlist[i]);
        }
    }
    // redlist 배열 자체를 해제
    free(redlist);
}
void    free_adcmd(t_adcmd *adcmd)
{
    t_adcmd *del_node;

    del_node = adcmd;
    while(adcmd != NULL)
    {
        adcmd = adcmd->next;
        free_old_argv(del_node->argv);
        free_redlist(del_node->redlist, del_node->redlist_count);
        free(del_node);
        del_node = adcmd;
    }
}

void    free_cmd(t_cmd *cmd)
{
    t_cmd *del_cmd;

    del_cmd = cmd;
    while(cmd != NULL)
    {
        cmd = cmd->next;
        free(del_cmd->con);
        //free(del_cmd->type);
        free(del_cmd);
        del_cmd = cmd;
    }
}

void	free_tokens(char** toks, int tok_count)
{
	int i = 0;
	while (i < tok_count)
	{
		free(toks[i]);
		i++;
	}
	free(toks);
}

void	free_double(void **collection)
{
	int	i;

	i = 0;
	while (collection[i])
	{
		free(collection[i]);
		i++;
	}
	free(collection);
}
