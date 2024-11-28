#include "minishelltemp.h"

void	init_sh_list(t_sh *sh_list)
{
	int		i;
	int		n;
	void	*null_sh_list;

	n = sizeof(t_sh);
	i = 0;
	null_sh_list = (void *)sh_list;
	while (i < n)
	{
		((unsigned char *)null_sh_list)[i] = '\0';
		i++;
	}
}

void removeNodeValue(t_sh *sh_list, char *target)
{
    t_export *del_node;
    t_export *prev_node;

    if (sh_list->export_head == NULL)
        return;

    if (ft_strncmp(sh_list->export_head->key, target, ft_strlen(target)) == 0 &&
        sh_list->export_head->key[ft_strlen(target)] == '\0') // 정확히 key와 일치
    {
        del_node = sh_list->export_head;
        sh_list->export_head = sh_list->export_head->next;
        free(del_node->key);
        if (del_node->value)
            free(del_node->value);
        free(del_node);
        return;
    }
		del_node = sh_list->export_head->next;
    while (del_node != NULL)
    {
        if (ft_strncmp(del_node->key, target, ft_strlen(target) ) == 0 &&
            del_node->key[ft_strlen(target)] == '\0') // 정확히 key와 일치
        {
            prev_node->next = del_node->next;
            free(del_node->key);
            if (del_node->value)
                free(del_node->value);
            free(del_node);
            return;
        }
        prev_node = del_node;
        del_node = del_node->next;
    }
    	prev_node = sh_list->export_head;
 
}

void working_unset(t_sh *sh_list, char *cmd)
{
    char **ept_temp;
    int i;

    ept_temp = ft_split(cmd, ' ');
    if (ept_temp == NULL)
        return;

    i = 1;
    int j = 1;
    while(ept_temp[j])
    {
        printf("ept_temp : %s\n", ept_temp[j]);
        j ++;
    }
    while (ept_temp[i])
    {
		printf("ept_temp : %s", ept_temp[i]);
        removeNodeValue(sh_list, ept_temp[i]);
        i++;
    }

    i = 0;
    while (ept_temp[i])
    {
        free(ept_temp[i]);
        i++;
    }
    free(ept_temp);
}

 
int main(int argc, char **argv, char **envp)
{
    char cmd[100];
	char **ept_temp;
    t_sh sh_list;

	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);
	if (argc == 1)
	{
		while(1)
    	{	
        	printf("명령어를 입력해 주세요\n");
        	 fgets(cmd, sizeof(cmd), stdin);
             cmd[strlen(cmd)-1] = '\0'; 
        	if (ft_strncmp(cmd, "env", 3) == 0)
			{
            	print_export_list(sh_list.export_head);
			}
			else if (ft_strncmp(cmd, "export", 6) == 0)
			{
				// 명령어 분리
                ept_temp = ft_split(cmd, ' ');
                if (ept_temp[1] == NULL) // export만 입력한 경우
                {
                    print_export_list2(sh_list.export_head);
                }
                else // export와 함께 key=value 입력
                {
                    insert_envp(ept_temp, &sh_list); // 분리된 인자를 처리
                }
			}
			else if (ft_strncmp(cmd, "unset", 5) == 0)
			{
				working_unset(&sh_list, cmd);
			}
            else if (ft_strncmp(cmd, "pwd", 3) == 0)
            {
                ft_pwd();
            }
    	}
	}

}