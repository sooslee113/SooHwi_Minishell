/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:24:16 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/25 16:50:26 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 동적 할당된 토큰 메모리 해제
void	free_tokens(char** toks, int tok_count)
{
	int i = 0;
	while (i < tok_count)
	{
		free(toks[i]);
		i++;
	}
	free(toks);
}

// 현재 토큰을 tokens에 추가하는 함수
void	add_token(t_tokenizer *tok)
{
	if (tok->char_i > 0)
	{
		tok->curr_tok[tok->char_i] = '\0';
		tok->toks[(tok->tok_i)++] = ft_strdup(tok->curr_tok);//할당
		tok->char_i = 0;
	}
}

void	init_tokenizer(t_tokenizer *tok)
{
	int	i;

	i = 0;
	tok->toks = malloc(sizeof(char *) * 256);//할당
	if (tok->toks == NULL)
		exit(1);
	while (tok->curr_tok[i] != 0)
	{
		tok->curr_tok[i] = '\0';
		i++;
	}
	tok->tok_i = 0;
	tok->char_i = 0;
	tok->one_qut = 0;
	tok->two_qut = 0;
	tok->c = 0;
	tok->next_c = 0;
	tok->pipe_cnt = 0;
}

void	take_pipe_and_anglebracket(t_tokenizer *tok, int *i)
{
	add_token(tok);
	tok->curr_tok[0] = tok->c;
	if (tok->c == '|')
		tok->pipe_cnt++;
	if ((tok->c == '>' && tok->next_c == '>')\
		|| (tok->c == '<' && tok->next_c == '<')\
		|| (tok->c == '|' && tok->next_c == '|')\
		|| (tok->c == '<' && tok->next_c == '>')\
		|| (tok->c == ';' && tok->next_c == ';'))//11/25 15:00_이거 추가
	{
		tok->curr_tok[1] = tok->next_c;
		tok->curr_tok[2] = '\0';
		(*i)++;
	}
	else
		tok->curr_tok[1] = '\0';
	tok->toks[tok->tok_i++] = ft_strdup(tok->curr_tok);
}

void	split_if_else_part(t_tokenizer *tok, int *i)
{
	if (tok->one_qut != 0 || tok->two_qut != 0)
	{
		if ((tok->c == '\'' && tok->one_qut) || (tok->c == '"' && tok->two_qut))
		{
			tok->one_qut = 0;
			tok->two_qut = 0;
		}
		else
			tok->curr_tok[tok->char_i++] = tok->c;
	}
	else if (ft_isspace(tok->c) != 0)
		add_token(tok);
	else if (tok->c == '\'' || tok->c == '"')
	{
		if (tok->c == '\'')
			tok->one_qut = 1;
		else
			tok->two_qut = 1;
	}
	else if (ft_strchr("|<>;", tok->c))//파이프 및 꺽쇠는 따로 처리
		take_pipe_and_anglebracket(tok, i);
	else
		tok->curr_tok[tok->char_i++] = tok->c;
}

// 문자열을 공백, 따옴표, 특수 문자로 나누는 함수
char** tokenize_split(char* input, int* token_count, int *pipe_cnt)
{
	int			i;
	t_tokenizer	tok;

	i = 0;
	init_tokenizer(&tok);
	while (input[i] != '\0')
	{
		tok.c = input[i];
		tok.next_c = input[i + 1];
		split_if_else_part(&tok, &i);
		i++;
	}
	add_token(&tok);
	tok.toks[tok.tok_i] = NULL;
	*token_count = tok.tok_i;
	*pipe_cnt = tok.pipe_cnt;

	return (tok.toks);
}
