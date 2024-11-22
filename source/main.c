/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/19 10:10:53 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_sh_list(t_sh *sh_list)
{
	int		i;
	int		n;
	void	*null_sh_list;

	n = sizeof(t_sh);
	i = 0;
	null_sh_list = (void *)sh_list;
	while (i < n)
	{
		((unsigned char *)null_sh_list)[i] = '\0';
		i++;
	}
}

int	main(int ac, char** av, char **envp)
{
	t_sh 	sh_list;
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
		tokenize_input(input, &sh_list);
		free(input);
	}
	printf("The End!\n");
	return (0);
}
