/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/26 01:40:02 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_sh_list(t_sh *sh_list)
{
	sh_list->export_head = NULL;
	sh_list->pipe_cnt = 0;
	// 필요한 멤버 추가 초기화
}


int	main(int ac, char** av, char **envp)
{
	t_sh 	sh_list;
	t_cmd	*head_cmd;
	char	*input;

	(void)ac;
	(void)av;
	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);
	sig_handle(&sh_list);

	while(1)
	{
		input = readline("minishell$ ");
		if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
			break;
		if(*input)
			add_history(input);
		head_cmd = tokenize_input(input, &sh_list);//head_cmd에는 모든 명령어 각각이 t_cmd형태로 토크나이징 및 타입이 지정되어 있음.
		//execute(&sh_list, head_cmd, envp);
		
		t_cmd *curr_cmd = head_cmd;//테스트 코드
		for (;curr_cmd != NULL; curr_cmd = curr_cmd->next)////////////////
			printf("cmd : %s / type : %d\n", curr_cmd->content, curr_cmd->type);//////////////////
		
		free(input);
	}
	printf("The End!\n");
	return (0);
}
