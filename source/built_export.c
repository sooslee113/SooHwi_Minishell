/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:28:47 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/29 02:49:50 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// 여기 부터는 export
void new_key_value_parsing(char *str, char **t_key, char **t_value)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '=')
		{
			*t_key = ft_substr(str, 0, i); 
			*t_value = ft_substr(str, i + 1, ft_strlen(str) - i - 1); 
			return;
		}
		i++;
	}
	*t_key = ft_strdup(str);
	*t_value = NULL; // 값이 없는 경우 NULL
}

int export_edgecase(char *key)
{
	int i = 0;

	if (!key)
		return (0);
	if (key[0] != '_' && ft_isalpha(key[0]) == 0)
		return (0); // 잘못된 시작 문자

	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (0); // 유효하지 않은 문자
		i++;
	}
	return (1);
}

void add_export_list2(t_export **p_export, char *t_key, char *t_value)
{
	t_export *new_node;
	t_export *temp_head = *p_export;

	// 기존 키 업데이트 처리
	while (temp_head != NULL)
	{
		if (ft_strcmp(temp_head->key, t_key) == 0)
		{
			if (t_value != NULL)
			{
				if (temp_head->value != NULL)
					free(temp_head->value);
				temp_head->value = ft_strdup(t_value);
			}
			return;
		}
		temp_head = temp_head->next;
	}

	// 새로운 노드 추가
	new_node = malloc(sizeof(t_export));
	if (!new_node)
		exit(1);
	new_node->key = ft_strdup(t_key);
	new_node->value = (t_value != NULL) ? ft_strdup(t_value) : NULL;
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

void divde_key_value(char *arg, t_sh *p_sh_list)
{
	char *t_key;
	char *t_value;

	new_key_value_parsing(arg, &t_key, &t_value);
	if (!export_edgecase(t_key)) // 키 유효성 검사
	{
		printf("Invalid KEY: %s\n", t_key);
		free(t_key); // 메모리 누수 방지
		free(t_value);
		return;
	}
	add_export_list2(&(p_sh_list->export_head), t_key, t_value);
	free(t_key);  // 메모리 해제
	free(t_value);
}

void insert_envp(t_cmd *cmd_node, t_sh *p_sh_list)
{
	while (cmd_node)
	{
		divde_key_value(cmd_node->con, p_sh_list);
		cmd_node = cmd_node->next;
	}
}

void free_temp(t_export *sorted_list)
{
	t_export *temp;
	while (sorted_list)
	{
		temp = sorted_list->next;
		free(sorted_list->key);
		if (sorted_list->value != NULL)
			free(sorted_list->value);
		free(sorted_list);
		sorted_list = temp;
	}
}

void list_copy(t_export **sorted_list, t_export *temp)
{
	while (temp)
	{
		t_export *new_node = malloc(sizeof(t_export));
		if (!new_node)
			exit(1);
		new_node->key = ft_strdup(temp->key);
		new_node->value = (temp->value != NULL) ? ft_strdup(temp->value) : NULL;
		new_node->next = *sorted_list;
		*sorted_list = new_node;
		temp = temp->next;
	}
}

void print_export_list2(t_export *export_head)
{
	t_export *sorted_list = NULL;
	t_export *temp = export_head;

	list_copy(&sorted_list, temp); // 리스트 복사
	envp_sort(&sorted_list);	  // 복사본 정렬

	temp = sorted_list;
	while (temp != NULL)
	{
		if (temp->value != NULL)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
	free_temp(sorted_list); // 복사본 메모리 해제
}
// 여기 까지 export
