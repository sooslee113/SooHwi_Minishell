/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:28:33 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 04:08:45 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_pipe(t_adcmd *ad_cmd)
{
	t_adcmd	*temp;

	while (ad_cmd != NULL)
	{
		temp = ad_cmd->next;
		if (ad_cmd->redlist)
		{
			free(ad_cmd->redlist->type);
			free(ad_cmd->redlist->file_name);
			free(ad_cmd->redlist);
		}
		free(ad_cmd);
		ad_cmd = temp;
	}
}

void init_pipe(t_adcmd **ad_cmd)   
{
	*ad_cmd = malloc(sizeof(t_adcmd));
	(*ad_cmd)->argv = NULL;
	(*ad_cmd)->exit_code = 1;
	(*ad_cmd)->pipe_fd[0] = 0;
	(*ad_cmd)->pipe_fd[1] = 0;
	(*ad_cmd)->pid = 0;
	(*ad_cmd)->redlist = malloc(sizeof(t_redlist));
	(*ad_cmd)->redlist->type = NULL;
	(*ad_cmd)->redlist->file_name = NULL;
	(*ad_cmd)->next = NULL;
	(*ad_cmd)->prev = NULL;
}

t_adcmd *create_pipe_node(t_adcmd **ad_cmd, t_adcmd *curr_node)
{
	t_adcmd	*new_pipe;

	init_pipe(&new_pipe); // 새 파이프 노드 초기화

	if (*ad_cmd == NULL) // 처음 생성되는 노드일 경우
	{
		*ad_cmd = new_pipe;
		return *ad_cmd;
	}
	else // 기존 노드가 있을 경우 연결
	{
		curr_node->next = new_pipe;
		new_pipe->prev = curr_node;
		return new_pipe;
	}
}

int count_cmd_segment(t_cmd *cmd)
{
	int	count;
		
	count = 0;
	while (cmd != NULL && cmd->type == N_WORD)
	{
		count++;
		cmd = cmd->next;
	}

	return count;
}

void fill_pipe_argv(t_adcmd *curr_node, t_cmd **cmd)
{
	int		i = 0;
	t_cmd	*temp_cmd = *cmd;

	while (temp_cmd != NULL && temp_cmd->type == N_WORD)
	{
	curr_node->argv[i] = ft_strdup(temp_cmd->con); // 명령어 복사
		temp_cmd = temp_cmd->next;
		i++;
	}
	curr_node->argv[i] = NULL; // argv의 마지막 요소 NULL
	curr_node->type = set_type(curr_node->argv[0]);
	*cmd = temp_cmd; // 현재 명령어 위치를 업데이트
}

t_adcmd *fill_in_pipe(t_cmd *cmd, t_adcmd *ad_cmd)
{
	t_cmd	*temp_cmd;
	t_adcmd	*curr_node = NULL;
	int		count;

	count = 0;
	temp_cmd = cmd;
	// 파이프 블록 처리
	while (temp_cmd != NULL)
	{
		// 새 t_adcmd 노드 초기화
		curr_node = create_pipe_node(&ad_cmd, curr_node);
		// 현재 파이프 세그먼트 크기 계산
		count = count_cmd_segment(temp_cmd);//순수명령어 단어 숫자 세기
		// argv 메모리 할당
		curr_node->argv = malloc(sizeof(char *) * (count + 1));
		// argv에 명령어 및 인자 복사
		fill_pipe_argv(curr_node, &temp_cmd);
		// 파이프 세그먼트가 끝난 경우, 다음으로 이동
		if (temp_cmd != NULL && temp_cmd->type != N_WORD)//파이프나 리다이렉션일 경우
			temp_cmd = temp_cmd->next;
	}

	return ad_cmd;
}