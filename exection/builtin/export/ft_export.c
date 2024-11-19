#include "../../../include/minishell.h"

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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (*ss1 != '\0' || *ss2 != '\0')
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
		i++;
	}
	return (0);
}

void	print_export_list(t_export *export_head)
{
	t_export *temp = export_head;

	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
void	divde_key_value(char **argv, t_export *export_head)
{

}
void	export_edgecase(char **argv)
{
	int i;
	int j;
	char **temp;
	
	i = 1;
	while(argv[i])
	{
		if (argv[i][0] != '_' || (ft_isalpha(argv[i][0]) == 0))
			return (1);
		i ++;
	}
	i = 1;
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if (ft_isalnum(argv[i][j]) == 0 || argv[i][j] != '_')
				return (1);
			j ++;
		}
		i ++;
	}
}
void	insert_envp(char ** argv, t_export *export_head)
{
	divde_key_value(argv);
	export_edgecase(argv);
}

int main(int argc, char **argv, char **envp)
{
    t_sh 	sh_list;

	(void)argc;
	(void)argv;
	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);
	if (argc == 1)
	{
		print_export_list(sh_list.export_head);
	}
	else if (argc > 1)
	{
		insert_envp((char **)argv, sh_list.export_head);
	}
    return (0);
}