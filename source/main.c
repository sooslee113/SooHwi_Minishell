/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 02:47:39 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_sh_list(t_sh *sh_list)
{
	sh_list->export_head = NULL;
	sh_list->pipe_cnt = 0;
	// 필요한 멤버 추가 초기화
}

void lets_free(char **str)
{
    int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
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
    sh_list.ad_cmd = NULL;
    //init_pipe(&ad_cmd);
	while(1)
	{
		input = readline("minishell$ ");
		if (!input) // citrl + d 는 인풋이 NULL이라는 뜻
			break;
		if(*input)
			add_history(input);
		sh_list.head_cmd = tokenize_input(input, &sh_list);//head_cmd에는 모든 명령어 각각이 t_cmd형태로 토크나이징 및 타입이 지정되어 있음.
        sh_list.ad_cmd = fill_in_pipe(sh_list.head_cmd, sh_list.ad_cmd);
		
		// t_cmd *curr_cmd = head_cmd;//테스트 코드
		// for (;curr_cmd != NULL; curr_cmd = curr_cmd->next) ////////////////
        // {
		// 	printf("cmd : %s / type : %d\n", curr_cmd->con, curr_cmd->type); //////////////////
        // }
        execute(&sh_list, envp);
		free(input);
	}
	printf("The End!\n");
	return (0);
}


/*
테스트 케이스
	//execute(&sh_list, head_cmd, envp);
		//echo 테스트
		// if (head_cmd && ft_strncmp(head_cmd->con, "echo", 4) == 0)
        // {
        //     ft_echo(head_cmd->next); // "echo" 이후의 명령어를 처리
        // }
		// else if (head_cmd && ft_strncmp(head_cmd->con, "env", 3) == 0) //env테스트
		// {
		// 	print_export_list(sh_list.export_head); // 환경 변수 출력
		// }
		// else if (head_cmd && ft_strncmp(head_cmd->con, "export", 6) == 0) // export 테스트
		// {
    	// 	if (head_cmd->next == NULL)
        // 		print_export_list2(sh_list.export_head); // export만 입력한 경우
    	// 	else
        // 		insert_envp(head_cmd->next, &sh_list); // key=value 입력 처리
		// }
        // else if (head_cmd && ft_strncmp(head_cmd->con, "unset", 5) == 0)
        // {
        //     if (head_cmd->next)
        //     {  // unset 명령어 뒤에 값이 있을 때만 처리
        //         while(head_cmd->next != NULL)
        //         {
        //             working_unset(&sh_list, head_cmd->next->con);
        //             head_cmd = head_cmd -> next;
        //         }
        //     } // unset 명령어 처리
        // }
		// else if (head_cmd && ft_strncmp(head_cmd->con, "pwd", 3) == 0)
		// {
		// 	ft_pwd(); // 현재 디렉토리 출력
		// }
*/

        // // 파이프 확인용 디버깅
		// t_pipe *temp = ad_cmd;
        // while (temp != NULL)
        // {
        //     printf("Pipe command:\n");
        //     for (int i = 0; temp->argv[i] != NULL; i++)
        //     {
        //         printf("- %s\n", temp->argv[i]);
        //         printf("%d", temp->type);
        //     }
        //     temp = temp->next;
        // }