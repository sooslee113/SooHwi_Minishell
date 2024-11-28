/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:07 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/28 21:11:31 by donghwi2         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"


typedef enum s_type
{
	N_WORD,//		모든 일반문자
	N_PIP,// 		'|'
	N_PIPS,// 		'||' -> just error
	N_RED_OUT,// 	'>'
	N_RED_OUT_AP,// '>>'
	N_RED_IN,// 	'<'
	N_RED_HRDC,// 	'<<'
	N_SEMIC,// 		';'
	N_SEMICS,//		';;' -> just error
}t_type;

typedef struct s_cmd
{
	char			*con;
	t_type			type;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_tokenizer //토큰화 과정에서 사용할 구조체
{
	char	**toks;
	char	curr_tok[1024];
	int		tok_i;//생성된 토큰인덱스 추적; toks에서 현재까지 저장된 토큰갯수 나타냄
	int		char_i;//현재 처리중인 토큰(curr_tok)내부에서 문자위치 추적
	int		one_qut;//single_quote
	int		two_qut;//double_quote
	int		pipe_cnt;//파이프 갯수 세기
	char	c;
	char	next_c;
}t_tokenizer;

typedef struct s_export //환경변수 -> 순서 오름차순
{
	char			*key;
	char			*value;
	struct s_export	*next;
}t_export, t_env;

typedef struct s_sh //통합(mini"sh"ell)구조체
{
	t_export			*export_head;//추후 env 및 export 방향성에 따라 추가 혹은 제거
	struct sigaction	sa;
	int					pipe_cnt;
}t_sh;

typedef struct s_redlist //
{
	char *type;
	char *file_name;
}t_redlist;

typedef struct s_pipe // pipe 구조체
{
	char **argv;
	int exit_code;
	int *fd;
	pid_t   pid;
	t_redlist *redlist;
	struct s_pipe *next;
	struct s_pipe *prev;
}t_pipe;

//error.c
void		print_error_and_exit(char *err_msg);

//execute.c
void		execute(t_sh *sh_list, t_cmd *head_cmd, char **envp);

//main.c
void		init_sh_list(t_sh *sh_list);

// //parsing_env.c
// void		add_env_list(t_env **p_env, char *t_key, char *t_value);

//parsing_envp.c
void		parsing_envp(char **envp, t_sh *p_sh_list);

//parsing_export.c
void		add_export_list(t_export **p_export, char *t_key, char *t_value);
void		split_list(t_export *head, t_export **front, t_export **back);
t_export	*sorted_merge(t_export *a, t_export *b);
void		envp_sort(t_export **export_head);

//sinal.c
void		sig_handler(int sig);
void		sig_handle(t_sh *sh_list);

//tokenize_input.c
int			check_quote_num(char *input);
t_cmd		*tokenize_input(char *input, t_sh *sh_list);

//tokenize_split.c
char** 		tokenize_split(char* input, int* token_count, int *pipe_cnt);
void		free_tokens(char** toks, int tok_count);

//util.c
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isspace(int c);
void		ft_lstadd_back_2(t_cmd *lst, t_cmd *new);

//builtin
void ft_echo(t_cmd *cmd);

#endif