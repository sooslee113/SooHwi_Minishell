#include "../include/minishell.h"
//libft 스핀오프

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

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c =='\n')
		return (1);
	else
		return (0);
}

void	ft_lstadd_back_2(t_cmd *lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (lst == NULL || new == NULL)
		return ;
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
	{
		print_error_and_exit("malloc errror");
		return (NULL);
	}
	return (ret);
}


// void	init_cmd_node()
// {	
// 	ft_bzero(sh_list->cmd.command, 128);
// 	while (i < 128)
// 	{
// 		ft_bzero(sh_list->cmd.args[i], 1024);
// 		i++;
// 	}
// 	sh_list->cmd.is_builtin = 0;
// 	sh_list->cmd.input_redir = 0;
// 	sh_list->cmd.output_redir = 0;
// }