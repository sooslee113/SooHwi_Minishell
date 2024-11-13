/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/12 15:33:40 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char** av, char **envp)
{
	t_sh sh_list;

	///
	if (ac == 100000 && av == NULL)
		av = NULL;
	///
	parsing_envp(envp, &sh_list);

	for (int m = 0; m < 10; m++)
		printf("%s, %s\n", sh_list.envs.key, sh_list.envs.value);
	// while (1)
	// {
	//		
	// }
	printf("The End!\n");
	return (0);
}