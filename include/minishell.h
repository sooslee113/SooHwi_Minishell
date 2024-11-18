/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:07 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/18 21:52:53 by donghwi2         ###   ########.fr       */
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

typedef struct s_export //환경변수 -> 순서 오름차순
{
	char			*key;
	char			*value;
	struct s_export	*next;
}t_export;

typedef struct s_cmd //명령어
{
	char	*command;//"export" 저장
	int		is_builtin;
	int		is_heredoc;
	char	**inja;
	//...
}t_cmd;

typedef struct s_sh //통합(mini"sh"ell)구조체
{
	t_env				*env_head;
	t_export			*export_head;//추후 env 및 export 방향성에 따라 추가 혹은 제거
	struct sigaction	sa;
	t_cmd				cmd;
}t_sh;

//main.c
void	init_sh_list(t_sh *sh_list);

//parsing_envc.c
void	add_env_list(t_env **p_env, char *t_key, char *t_value);

//parsing_envp.c
void	parsing_envp(char **envp, t_sh *p_sh_list);

//parsing_export.c
void	add_export_list(t_export **p_export, char *t_key, char *t_value);
void split_list(t_export *head, t_export **front, t_export **back);
t_export *sorted_merge(t_export *a, t_export *b);
void envp_sort(t_export **export_head);

//sinal
void	sig_handler(int sig);
void	sig_handle(t_sh *sh_list);

//util
int	ft_strcmp(const char *s1, const char *s2);


#endif