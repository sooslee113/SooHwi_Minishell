/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:28:41 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 02:28:42 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// 이건 env
void	print_export_list(t_export *export_head)
{
	t_export *temp = export_head;

	while (temp != NULL)
	{
		if (temp->value != NULL)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
// 여기까지가 env
