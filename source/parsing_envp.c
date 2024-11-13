/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:31:19 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/13 20:21:53 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_env_list(t_env *p_env, char *t_key, char *t_value)
{
	if (p_env != NULL)
	{
		while (p_env != NULL)
			p_env = p_env->next;
	}
	p_env = malloc(sizeof(t_env));
	if (p_env == NULL)
		exit(1);
	p_env->key = ft_strdup(t_key);
	p_env->value = ft_strdup(t_value);
	p_env->next = NULL;
				printf("envp->key : %s\n", p_env->key);///
	
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
		add_env_list(&(p_sh_list->envs), t_key, t_value);
				printf("p_sh_list->envs.key : %s\n", p_sh_list->envs.key);///
		
		i++;
	}
}
