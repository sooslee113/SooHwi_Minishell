/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:24:16 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/19 18:55:32 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 현재 토큰을 tokens에 추가하는 함수
void add_token(t_tokenizer *tok)
{
	if (tok->char_i > 0)
	{
		tok->curr_tok[tok->char_i] = '\0';
		tok->toks[(tok->tok_i)++] = ft_strdup(tok->curr_tok);
		tok->char_i = 0;
	}
}

void	init_tokenizer(t_tokenizer *tok)
{
	int	i;

	i = 0;
	tok->toks = malloc(sizeof(char *) * 128);
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
}

void	split_if_else_part(t_tokenizer *tok)
{
	if (tok->one_qut || tok->two_qut)
	{
		if ((tok->c == '\'' && tok->one_qut) || (tok->c == '"' && tok->two_qut))
			tok->one_qut = tok->two_qut = 0;
		else
			tok->curr_tok[tok->char_i++] = tok->c;
	}
	else if (isspace(tok->c))
		add_token(tok);
	else if (tok->c == '\'' || tok->c == '"')
	{
		if (tok->c == '\'')
			tok->one_qut = 1;
		else
			tok->two_qut = 1;
	}
	else if (ft_strchr("|<>", tok->c))
	{
		add_token(tok);
		tok->curr_tok[0] = tok->c;
		tok->curr_tok[1] = '\0';
		tok->toks[tok->tok_i++] = ft_strdup(tok->curr_tok);
	}
	else
		tok->curr_tok[tok->char_i++] = tok->c;
}

// 문자열을 공백, 따옴표, 특수 문자로 나누는 함수
char** tokenize_split(char* input, int* token_count)
{
	int			i;
	t_tokenizer	tok;

	i = 0;
	init_tokenizer(&tok);
	while (input[i] != '\0')
	{
		tok.c = input[i];
		split_if_else_part(&tok);
		i++;
	}
	add_token(&tok);
	tok.toks[tok.tok_i] = NULL;
	*token_count = tok.tok_i;
	return (tok.toks);
}
// 동적 할당된 토큰 메모리 해제
void free_tokens(char** toks, int tok_count)
{
	int i = 0;
	while (i < tok_count)
	{
		free(toks[i]);
		i++;
	}
	free(toks);
}
// 테스트 함수
int main()
{
	char* command = "echo 'hello world' \"what the | fuck\" > file.txt";
	int tok_count = 0;
	char** toks = split_like_shell(command, &tok_count);
	printf("토큰들:\n");
	int i = 0;
	while (i < tok_count)
	{
		printf("토큰 %d: %s\n", i, toks[i]);
		i++;
	}
	free_tokens(toks, tok_count);
	return 0;
}