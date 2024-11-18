/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:55:33 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/18 22:05:09 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 기본 환경변수를 갖는 list의 뒤에 노드(key 및 value와 함께)를 추가하는 코드
void	add_export_list(t_export **p_export, char *t_key, char *t_value)
{
	t_export	*new_node;
	t_export	*temp_head;

	new_node = malloc(sizeof(t_export));
	if (new_node == NULL)
		exit(1);
	new_node->key = ft_strdup(t_key);
	new_node->value = ft_strdup(t_value);
	new_node->next = NULL;

	if (*p_export == NULL)
		*p_export = new_node;
	else
	{
		temp_head = *p_export;
		while (temp_head->next != NULL)
			temp_head = temp_head->next;
		temp_head->next = new_node;
	}
}

void split_list(t_export *head, t_export **front, t_export **back)
{
    t_export *slow = head;
    t_export *fast = head->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = head;
    *back = slow->next;
    slow->next = NULL;
}
// 두 정렬된 리스트를 병합하는 함수
t_export *sorted_merge(t_export *a, t_export *b)
{
    t_export *result = NULL;
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (ft_strcmp(a->key, b->key) <= 0)
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}
// 연결 리스트를 합병 정렬하는 함수
void envp_sort(t_export **export_head)
{
    t_export	*head = *export_head;
    t_export	*a = NULL;
    t_export	*b = NULL;
    if (head == NULL || head->next == NULL)
        return;
    split_list(head, &a, &b);
    envp_sort(&a);
    envp_sort(&b);
    *export_head = sorted_merge(a, b);
}