/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:58:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/27 13:41:50 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void sig_handler(int sig) 
{
    if (sig == SIGQUIT)
    {
        // printf("\nQuit!\n");
        // exit(1);
        printf("\nCtrl + \\\n");
        rl_on_new_line();    // 새 줄로 이동
        rl_replace_line("", 0); // 현재 입력 줄을 지움
        rl_redisplay();      // 프롬프트를 새로 표시 
    }
    else if (sig == SIGINT)
    {
        printf("\nCtrl + C\n");
        rl_on_new_line();    // 새 줄로 이동
        rl_replace_line("", 0); // 현재 입력 줄을 지움
        rl_redisplay();      // 프롬프트를 새로 표시    
    }
}

void	sig_handle(t_sh *sh_list)
{
	sh_list->sa.sa_handler = sig_handler;    // SIGINT 발생 시 handle_sigint 핸들러 호출
	sigemptyset(&(sh_list->sa.sa_mask));         // sa_mask를 빈 집합으로 초기화
	sigaddset(&(sh_list->sa.sa_mask), SIGQUIT);  // SIGQUIT 시그널을 sa_mask에 추가
	sh_list->sa.sa_flags = 0;
	if (sigaction(SIGINT, &(sh_list->sa), NULL) == -1) 
	{
        perror("sigaction");
        exit(EXIT_FAILURE);
	}
    else if (sigaction(SIGQUIT, &(sh_list->sa), NULL) == -1)
    {
                perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

