/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/11 15:36:24 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char** av, char **envp)
{
	t_sh sh_list;

	parsing_envp(envp, &sh_list);

	while (1)
	{
		
	}
	
}