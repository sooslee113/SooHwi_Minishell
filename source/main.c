/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/14 17:49:23 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	main(int ac, char** av, char **envp)
{
	t_sh sh_list;

	///
	if (ac == 100000 && av == NULL)
		av = NULL;
	///
	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);

	for (int m = 0; envp[m] != NULL; m++)
	{
		printf("%s=%s\n", sh_list.env_head->key, sh_list.env_head->value);
		sh_list.env_head = sh_list.env_head->next;
	}
	// while (1)
	// {
	//		
	// }
	printf("The End!\n");
	return (0);
}
