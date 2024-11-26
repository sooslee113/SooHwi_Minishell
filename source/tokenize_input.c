/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:24:04 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/26 18:02:23 by donghwi2         ###   ########.fr       */
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

t_type set_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return N_PIP;
	else if (ft_strcmp(token, "||") == 0)
		return N_PIPS;
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<>") == 0)
		return N_RED_OUT;
	else if (ft_strcmp(token, ">>") == 0)
		return N_RED_OUT_AP;
	else if (ft_strcmp(token, "<") == 0)
		return N_RED_IN;
	else if (ft_strcmp(token, "<<") == 0)
		return N_RED_HRDC;
	else if (ft_strcmp(token, ";") == 0)
		return N_SEMIC;
	else if (ft_strcmp(token, ";;") == 0)
		return N_SEMICS;
	else
		return N_WORD;
}

int validate_syntax(t_cmd *cmd_list)
{
	t_cmd 	*cur;
	char	*string;

	cur = cmd_list;
	string = "bash : syntax error near unexpected token";
	if (cur && (cur->type == N_PIP || cur->type == N_SEMIC))
		return (printf("%s '%s'\n", string, cur->con), 1);
	while (cur)
	{
		if (cur->type == N_PIP && (!cur->next || cur->next->type != N_WORD))
			return (printf("%s '|'\n", string), 1);
		else if ((cur->type == N_RED_OUT || cur->type == N_RED_OUT_AP\
			|| cur->type == N_RED_IN || cur->type == N_RED_HRDC)\
			&& (!cur->next || cur->next->type != N_WORD))// 리디션 뒤 WORD 없으면 에러
			return (printf("%s 'newline'\n", string), 1);
		else if (cur->type == N_PIPS || cur->type == N_SEMICS)
			return (printf("%s '%s'\n", string, cur->con), 1);
		cur = cur->next;
	}
	return (0); // 정상일 경우
}

t_cmd	*set_cmd_struct(char **toks)
{//toks배열을 순회하면서, head_cmd 포인터에 노드를 생성하고 content와 type 설정, 연결
	int		i;
	t_cmd	*head_cmd;
	t_cmd	*curr_cmd;

	i = 0;
	head_cmd = malloc(sizeof(t_cmd));
	head_cmd->con = ft_strdup(toks[i]);
	head_cmd->type = set_type(toks[i]);
	head_cmd->next = NULL;
	curr_cmd = head_cmd;
	i++;
	while (toks[i] != NULL)
	{
		curr_cmd->next = malloc(sizeof(t_cmd));
		curr_cmd = curr_cmd->next;
		curr_cmd->con = ft_strdup(toks[i]);
		curr_cmd->type = set_type(toks[i]);
		curr_cmd->next = NULL;
		i++;
	}
	return (head_cmd);
}

t_cmd	*tokenize_input(char *input, t_sh *sh_list)
{// input = "echo "hello" > file.txt"  ->  {"echo", "hello", ">" "file.txt"}
	char	**temp_toks;
	int		tok_cnt;//토큰 갯수 저장
	t_cmd	*head_cmd;

	if (*input == '\0')
		return (NULL);//아무것도안쳤을때 sigfault 방지
	tok_cnt = 0;
	if (check_quote_num(input) != 0)// 따옴표 짝 맞는지 먼저 보고 틀리면 에러 리턴
		exit(1);//에러 따로 처리
	temp_toks = tokenize_split(input, &tok_cnt, &(sh_list->pipe_cnt));//[tokenize_split.c] : 명령어 토큰으로 분해
	head_cmd = set_cmd_struct(temp_toks);
	if (validate_syntax(head_cmd) == 1)
		exit(1);//에러 따로 처리
	// 테스트 함수
	printf("-----\n");
	free_tokens(temp_toks, tok_cnt);
	return (head_cmd);
//
}

