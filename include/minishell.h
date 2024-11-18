/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:07 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/18 19:25:46 by sooslee          ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include "../libft/libft.h"

typedef struct s_env //환경변수 (단방향)연결리스트
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_sh //통합(mini"sh"ell)구조체
{
	t_env				*env_head;
	//t_export			*export_head;//추후 env 및 export 방향성에 따라 추가 혹은 제거
	struct sigaction	sa;
}t_sh;

//parsing_envp
void	parsing_envp(char **envp, t_sh *p_sh_list);
void	add_env_list(t_env **p_env, char *t_key, char *t_value);
void	init_sh_list(t_sh *sh_list);

//sinal
void	sig_handler(int sig);
void	sig_handle(t_sh *sh_list);



#endif