/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:31:19 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:28 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing_envp(char **envp, t_sh *sh_list)
{
	int		i;
	int		j;
	char	*t_key;
	char	*t_value;

	i = 0;
	while (envp[i] != '\0')
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
		add_env_list(&(sh_list->envs), t_key, t_value);
		i++;
	}
}

void	add_env_list(t_env *env, char *t_key, char *t_value)
{
	if (env != NULL)
	{
		while (env != NULL)
			env = env->next;
	}
	env = malloc(sizeof(t_env));
	if (env == NULL)
		
	env->key = ft_strdup(t_key);
	env->value = ft_strdup(t_value);
	env->next = NULL;
}
