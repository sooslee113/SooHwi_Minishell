/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:24:04 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/19 18:58:56 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize_input(char *input, t_sh *sh_list)
{// input = "echo "hello" > file.txt"  ->  {"echo", "hello", ">" "file.txt"}
	int		i;
	char	**temp_toks;
	int		tok_cnt;//토큰 갯수 저장

	i = 0;
	tok_cnt = 0;
	temp_toks = tokenize_split(input, &tok_cnt);//->tokenize_split.c : 명령어 토큰으로 분해
	while (input[i])
	{
		if (is_cmd(input[i]) == 1)
			add_token();
		i++;
	}
}