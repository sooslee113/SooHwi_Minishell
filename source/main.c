/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/18 18:18:19 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// sh_list는 통합 관리 리스트(shell list).
// 아래 코드는 sh_list를 0으로 초기화하는 코드.
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

// readline을 사용하여 명령어를 받는 예시 코드를 추가함.
// 실행을 해 보면 readline뒤의 문자가 출력되며, 입력받는 값을 리턴할 준비를 함.
// 즉, readline이 실행된 후 터미널에서 받는 명령어가 command포인터를 통해 반환됨.
// command포인터를 통해 반환된 명령어를 이제부터 파싱하면 될듯.
int	main(int ac, char** av, char **envp)
{
	t_sh 	sh_list;
	char *input;

	(void)ac;
	(void)av;
	init_sh_list(&sh_list);
	parsing_envp(envp, &sh_list);
	sig_handle(&sh_list);

	if (sigaction(SIGINT, &(sh_list.sa), NULL) == -1) 
	{
        perror("sigaction");
        exit(EXIT_FAILURE);
	}
	while(1)
	{
    input = readline("minishell$");
    if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
	break;
    if(*input)
	add_history(input);
    free(input);
	}
	printf("The End!\n");
	return (0);
}
