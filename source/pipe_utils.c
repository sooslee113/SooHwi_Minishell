#include "../include/minishell.h"


int    check_is_red(char *cmd)
{
    if(ft_strcmp(cmd, "<") == 0)
        return 0;
    else if(ft_strcmp(cmd, "<<") == 0)
        return 0;
    else if(ft_strcmp(cmd, ">") == 0)
        return 0;
    else if(ft_strcmp(cmd, ">>") == 0)
        return 0;
    else
        return (1);
}

// int     count_red(t_adcmd *cmd)
// {
//     int count;
//     t_adcmd *temp_head;
    
//     count = 0;
//     while()
//     {

//     }
// }