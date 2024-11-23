/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:24:04 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/23 17:24:54 by donghwi2         ###   ########.fr       */
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

void	tokenize_input(char *input, t_sh *sh_list)
{// input = "echo "hello" > file.txt"  ->  {"echo", "hello", ">" "file.txt"}
//	int		i;
	char	**temp_toks;
	int		tok_cnt;//토큰 갯수 저장

//	i = 0;
	tok_cnt = 0;
	if (check_quote_num(input) != 0)
		return ;
	temp_toks = tokenize_split(input, &tok_cnt);//->tokenize_split.c : 명령어 토큰으로 분해
// 	while (input[i])
// 	{
// 		if (is_cmd(input[i]) == 1)//유효한 명령어인지 확인
// 			add_token();
// 		i++;
// 	}

	// 테스트 함수
	printf("-----\n");
	for (int j = 0; j < tok_cnt; j++)
		printf("토큰 %d: %s\n", j, temp_toks[j]);
	free_tokens(temp_toks, tok_cnt);
	(void)sh_list;//임시
//
}