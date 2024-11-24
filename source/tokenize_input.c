/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:24:04 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/24 19:38:18 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_num(char *input)// 따옴표 짝 맞는지 먼저 보고 틀리면 에러 리턴
{
	int	one_flag;
	int	two_flag;

	one_flag = 0;
	two_flag = 0;
	while (*input != '\0')
	{
		if (*input == '\'' && two_flag % 2 == 0)
			one_flag++;
		else if (*input == '"' && one_flag % 2 == 0)
			two_flag++;
		input++;
	}
	if (one_flag % 2 != 0 || two_flag % 2 != 0)
	{
		printf("quote error\n");
		return (1);
	}
	return (0);
}

void	init_cmd_util(t_temp_1 *tls, int pipe_c, t_cmd *head_cmd)
{
	t_cmd	*temp_cmd;
	int		arg_i;

	(tls->curr_cmd)->command = ft_strdup(tls->tt[tls->i]);//명령어 저장하는 곳
	arg_i = 0;
	(tls->curr_cmd)->args = malloc(sizeof(char *) * 128);
	tls->i++;// 명령어 뒤의 인자 저장하는 곳
	while (tls->tt[tls->i] != NULL && ft_strcmp(tls->tt[tls->i], "|") != 0)
	{
		(tls->curr_cmd)->args[arg_i] = ft_strdup(tls->tt[tls->i]);
		tls->i++;
		arg_i++;
	}
	(tls->curr_cmd)->args[arg_i] = NULL;
	if (pipe_c > 0 && tls->tt[tls->i] && ft_strcmp(tls->tt[tls->i], "|") == 0)
	{
		temp_cmd = malloc(sizeof(t_cmd));
		ft_lstadd_back_2(head_cmd, temp_cmd);
		tls->curr_cmd = (tls->curr_cmd)->next;
		tls->i++;
	}
	else
		(tls->curr_cmd)->next = NULL;
}

t_cmd	*init_cmd_struct(char **temp_toks, int pipe_cnt)
{
	t_temp_1	tls;
	t_cmd		*head_cmd;
	
	tls.i = 0;
	head_cmd = malloc(sizeof(t_cmd));
	tls.curr_cmd = head_cmd;
	tls.tt = temp_toks;
	while (pipe_cnt >= 0)
	{
		init_cmd_util(&tls, pipe_cnt, head_cmd);
		pipe_cnt--;
	}
	return (head_cmd);
}

void	tokenize_input(char *input, t_sh *sh_list)
{// input = "echo "hello" > file.txt"  ->  {"echo", "hello", ">" "file.txt"}
	char	**temp_toks;
	int		tok_cnt;//토큰 갯수 저장

	tok_cnt = 0;
	if (check_quote_num(input) != 0)// 따옴표 짝 맞는지 먼저 보고 틀리면 에러 리턴
		return ;
	temp_toks = tokenize_split(input, &tok_cnt, &(sh_list->pipe_cnt));//[tokenize_split.c] : 명령어 토큰으로 분해


	sh_list->cmd = init_cmd_struct(temp_toks, sh_list->pipe_cnt);

	// 테스트 함수
	printf("-----\n");
	for (int j = 0; j < tok_cnt; j++)
		printf("토큰 %d: %s\n", j, temp_toks[j]);
	printf("command : %s\n", (sh_list->cmd)->command);
	printf("args : %s\n", (sh_list->cmd)->args[0]);
	printf("args : %s\n", (sh_list->cmd)->args[1]);
	free_tokens(temp_toks, tok_cnt);
//
}