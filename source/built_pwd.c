/* ************************************************************************** */
/*									                                        */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:28:26 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 02:28:27 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// 여기 부터 pwd
void	ft_pwd()
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
		printf("%s\n", cwd);
	} 
	else 
	{
		perror("getcwd");
		return ;
	}
	return ;
}
// 여기 까지가 pwd