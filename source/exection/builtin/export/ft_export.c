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

void	new_key_value_parsing(char *str, char **t_key, char **t_value)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
		{
			*t_key = ft_substr(str, 0 , i);
			*t_value = ft_substr(str, i + 1, ft_strlen(str) -i -1);
			return ;
		}
		i ++;
	}
	*t_key = str;
	*t_value = NULL;
}

int	export_edgecase(char *key)
{
	int i;

	if (!key)
		return (0);
	if (key[0] != '_' && (ft_isalpha(key[0]) == 0))
		return (0);
	i = 1;
	while(key[i])
	{
		if (ft_isalnum(key[i]) == 0 || key[i] != '_')
			return (0);
		i ++;
	}
	return (1);
}
void	divde_key_value(char **argv, t_sh *p_sh_list)
{
	int i;
	char *t_key;
	char *t_value;

	i = 1;
	while(argv[i])
	{
		new_key_value_parsing(argv[i], &t_key, &t_value);
		if (export_edgecase(t_key) == 0)
		{
			printf("invaild KEY\n");
				return ; //예외 처리
		}
		add_export_list(&(p_sh_list->export_head), t_key, t_value);
		envp_sort(&(p_sh_list->export_head));
		i ++;
	}
}


void	insert_envp(char **argv, t_sh *p_sh_list)
{
	divde_key_value(argv, p_sh_list);
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
		insert_envp((char **)argv, &(sh_list));
		print_export_list(sh_list.export_head);
	}
    return (0);
}