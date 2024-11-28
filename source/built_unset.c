/* ************************************************************************** */
/*																	        */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:28:22 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 02:28:23 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// 여기서 부터는 unset

void removeNodeValue(t_sh *sh_list, char *target)
{
	t_export *del_node;
	t_export *prev_node;

	if (sh_list->export_head == NULL)
		return;

	// 첫 번째 노드를 처리
	if (ft_strncmp(sh_list->export_head->key, target, ft_strlen(target)) == 0)
	{
		del_node = sh_list->export_head;
		sh_list->export_head = sh_list->export_head->next;
		free(del_node->key);
		if (del_node->value)
			free(del_node->value);
		free(del_node);
		printf("Removed node with key: %s\n", target); // 삭제된 노드 확인
		return;
	}

	// 이후 노드를 처리
	prev_node = sh_list->export_head;
	del_node = sh_list->export_head->next;
	while (del_node != NULL)
	{
		if (ft_strncmp(del_node->key, target, ft_strlen(target)) == 0)
		{
			prev_node->next = del_node->next;
			free(del_node->key);
			if (del_node->value)
				free(del_node->value);
			free(del_node);
			printf("Removed node with key: %s\n", target); // 삭제된 노드 확인
			return;
		}
		prev_node = del_node;
		del_node = del_node->next;
	}
}

void working_unset(t_sh *sh_list, char *cmd)
{
	char **ept_temp;
	int i;

	ept_temp = ft_split(cmd, ' ');
	if (ept_temp == NULL)
	{
		printf("Error: ft_split failed\n");
		return;
	}
	/* 디버깅용*/
		i = 0;
	while(ept_temp[i])
	{
		printf("ept_temp[%d] = %s ", i,ept_temp[i]);
		i ++;
	}
	/* 여기까지 */
	i = 0; // ept_temp에는 삭제할 키 값이 있다.
	while (ept_temp[i]) // `ept_temp[0]`부터 시작하여 처리
	{
		printf("Unset target: %s\n", ept_temp[i]); // unset 명령어 뒤에 인자 출력
		removeNodeValue(sh_list, ept_temp[i]); // 해당 키를 export list에서 삭제
		i++;
	}

	// ept_temp 메모리 해제
	i = 0;
	while (ept_temp[i])
	{
		free(ept_temp[i]);
		i++;
	}
	free(ept_temp);
}
// 여기 까지가 unset
