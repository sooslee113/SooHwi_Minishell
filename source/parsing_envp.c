/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:31:19 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/15 15:56:08 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



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
		add_env_list(&(p_sh_list->env_head), t_key, t_value);
		i++;
	}
}
