#include "../../../include/minishell.h"

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

void	add_export_list(t_export **p_export, char *t_key, char *t_value)
{
	t_export	*new_node;
	t_export	*temp_head;

	new_node = malloc(sizeof(t_export));
	if (new_node == NULL)
		exit(1);
	new_node->key = ft_strdup(t_key);
	new_node->value = ft_strdup(t_value);
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

void	add_env_list(t_env **p_env, char *t_key, char *t_value)
{
	t_env	*new_node;
	t_env	*temp_head;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		exit(1);
	new_node->key = ft_strdup(t_key);
	new_node->value = ft_strdup(t_value);
	new_node->next = NULL;

	if (*p_env == NULL)
		*p_env = new_node;
	else
	{
		temp_head = *p_env;
		while (temp_head->next != NULL)
			temp_head = temp_head->next;
		temp_head->next = new_node;
	}
}

void	parsing_envp(char **envp, t_sh *p_sh_list)
{
	int		i;
	int		j;
	char	*t_key;
	char	*t_value;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '\0')
		{
			if (envp[i][j] == '=')
			{
				t_key = ft_substr(envp[i], 0, j);
				t_value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
			}
			j++;
		}
		add_export_list(&(p_sh_list->export_head), t_key, t_value);
		add_env_list(&(p_sh_list->env_head), t_key, t_value);
		i++;
	}
}

void	print_env_list(t_env *env_head)
{
	t_env *temp = env_head;

	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_sh sh_list;

	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);
	if (argc == 2 && ft_strcmp(argv[1], "env") == 0)
		print_env_list(sh_list.env_head);
	else
	{
		printf("error");
		exit(0);
	}
}

