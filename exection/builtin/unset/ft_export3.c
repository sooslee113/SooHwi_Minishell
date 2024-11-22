#include "minishelltemp.h"


void free_temp(t_export *sorted_list, t_export *temp)
{
	while (sorted_list)
    {
        temp = sorted_list->next;
        free(sorted_list->key);
        if (sorted_list->value != NULL)
        {
            free(sorted_list->value);
        }
        free(sorted_list);
        sorted_list = temp;
    }
}

void list_copy(t_export **sorted_list, t_export *temp)
{
	while (temp)
    {
        t_export *new_node;
		new_node = malloc(sizeof(t_export));
		if (!new_node)
			exit(1);
        new_node->key = ft_strdup(temp->key);
        if (temp->value != NULL)
            new_node->value = ft_strdup(temp->value);
        else
            new_node->value = NULL;

        new_node->next = *sorted_list;
        *sorted_list = new_node;
        temp = temp->next;
    }
}
void print_export_list2(t_export *export_head)
{

    t_export *sorted_list;
    t_export *temp;

	sorted_list = NULL;
	temp = export_head;
	// 1. 리스트 복사
	list_copy(&sorted_list, temp);
    // 2. 복사본 리스트 정렬
    envp_sort(&sorted_list);
    // 3. 정렬된 리스트 출력
    temp = sorted_list;
    while (temp != NULL)
    {
        if (temp->value != NULL)
            printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
        else
            printf("declare -x %s\n", temp->key); // 값이 없는 경우
        temp = temp->next;
    }
    // 4. 복사본 리스트 메모리 해제
	free_temp(sorted_list, temp);
}
