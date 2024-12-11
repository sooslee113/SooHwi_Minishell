/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/10 16:35:49 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_sh_list(t_sh *sh_list)
{
	sh_list->export_head = NULL;
	sh_list->pipe_cnt = 0;
	// 필요한 멤버 추가 초기화
}

void print_adcmd_node(t_adcmd *node, int node_num)
{
    if (!node)
        return;

    printf("\n=== Command Node %d ===\n", node_num);
    
    // Print argv contents
    printf("Arguments:\n");
    if (node->argv)
    {
        for (int i = 0; node->argv[i]; i++)
        {
            printf("  argv[%d]: '%s'\n", i, node->argv[i]);
        }
    }
    else
    {
        printf("  No arguments\n");
    }

    // Print redirection information
    printf("\nRedirections:\n");
    if (node->redlist && node->redlist_count > 0)
    {
        for (int i = 0; i < node->redlist_count; i++)
        {
            if (node->redlist[i])
            {
                printf("  Redirection %d:\n", i);
                printf("    Type: ");
                switch (node->redlist[i]->type)
                {
                    case N_RED_IN:
                        printf("Input (<)\n");
                        break;
                    case N_RED_OUT:
                        printf("Output (>)\n");
                        break;
                    case N_RED_OUT_AP:
                        printf("Append (>>)\n");
                        break;
                    case N_RED_HRDC:
                        printf("Heredoc (<<)\n");
                        break;
                    default:
                        printf("Unknown (%d)\n", node->redlist[i]->type);
                }
                printf("    File: '%s'\n", node->redlist[i]->file_name ? 
                       node->redlist[i]->file_name : "NULL");
            }
        }
    }
    else
    {
        printf("  No redirections\n");
    }

    // Print pipe information
    printf("\nPipe Status:\n");
    printf("  pipe_fd[0]: %d\n", node->pipe_fd[0]);
    printf("  pipe_fd[1]: %d\n", node->pipe_fd[1]);
    printf("  Process ID: %d\n", node->pid);
}

void print_all_adcmd(t_sh *sh_list)
{
    t_adcmd *current;
    int node_count;

    if (!sh_list || !sh_list->ad_cmd)
    {
        printf("No command nodes found.\n");
        return;
    }

    printf("\n====== COMMAND STRUCTURE DUMP ======\n");
    printf("Total pipes: %d\n", sh_list->pipe_cnt);
    
    current = sh_list->ad_cmd;
    node_count = 0;

    while (current)
    {
        print_adcmd_node(current, node_count);
        current = current->next;
        node_count++;
    }

    printf("\nTotal nodes: %d\n", node_count);
    printf("================================\n\n");
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
		sh_list.head_cmd = tokenize_input(input, &sh_list); //head_cmd에는 모든 명령어 각각이 t_cmd형태로 토크나이징 및 타입이 지정되어 있음.
        fill_in_adcmd(&(sh_list), sh_list.head_cmd);	
        
        t_cmd *curr_cmd = sh_list.head_cmd;//테스트 코드
		for (;curr_cmd != NULL; curr_cmd = curr_cmd->next)
        {
			printf("cmd : %s / type : %d\n", curr_cmd->con, curr_cmd->type);
        }
        // ad_cmd 내용 출력
        // printf("Command arguments:\n");
        // for (int i = 0; sh_list.ad_cmd->argv && sh_list.ad_cmd->argv[i]; i++) {
        //     printf("argv[%d]: %s\n", i, sh_list.ad_cmd->argv[i]);
        // }
        // for (int i = 0; i < sh_list.ad_cmd->redlist_count; i++) 
        // {
        //     printf("Redirection Type: %d, File: %s\n",
        //    sh_list.ad_cmd->redlist[i]->type,
        //    sh_list.ad_cmd->redlist[i]->file_name);
        // }
        print_all_adcmd(&sh_list);
        //execute(&sh_list, envp);
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
/*

*/