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
			else if (ft_strncmp(cmd, "unset", 6) == 0)
			{

			}
    	}
	}
	else if (ft_strcmp(argv[1], "hello"))
		printf("hello world");
}