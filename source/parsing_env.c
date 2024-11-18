/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:54:40 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/18 20:54:55 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 기본 환경변수를 갖는 list의 뒤에 노드(key 및 value와 함께)를 추가하는 코드
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