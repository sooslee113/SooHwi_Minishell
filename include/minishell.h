/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:07 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/12 15:51:24 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include "../libft/libft.h"

typedef struct s_env //환경변수 (단방향)연결리스트
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_sh //통합(mini"sh"ell)구조체
{
	t_env	envs;
}t_sh;

void	parsing_envp(char **envp, t_sh *p_sh_list);
void	add_env_list(t_env *p_env, char *t_key, char *t_value);

#endif