#include "minishelltemp.h"

void	new_key_value_parsing(char *str, char **t_key, char **t_value)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
		{
			*t_key = ft_substr(str, 0 , i);
			*t_value = ft_substr(str, i + 1, ft_strlen(str) -i -1);
			return ;
		}
		i ++;
	}
	*t_key = ft_strdup(str);
	printf("t_key %s\n", *t_key);
	*t_value = NULL;
}

int	export_edgecase(char *key)
{
	int i;

	if (!key)
		return (0);
	if (key[0] != '_' && (ft_isalpha(key[0]) == 0))
	{
		printf("Invalid start character: %c\n", key[0]); // 디버깅용
		return (0);
	}
	i = 0;
	printf("key 길이 : %ld\n", ft_strlen(key));
	while(key[i])
	{
		printf("key[%d] :%c ", i,key[i]);
		if (key[i] == '\n')
			printf("hellod");

		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			printf("Invalid character in key: %c %d\n", key[i], i);
			return (0);
		}
		i ++;
	}
	return (1);
}
void	add_export_list2(t_export **p_export, char *t_key, char *t_value)
{
	t_export	*new_node;
	t_export	*temp_head;

	    temp_head = *p_export;
    while (temp_head != NULL)
    {
        if (ft_strcmp(temp_head->key, t_key) == 0) // 기존 키와 동일한지 확인
        {
            // 새로운 값이 존재할 경우에만 업데이트
            if (t_value != NULL)
            {
                if (temp_head->value != NULL)
                {
                    free(temp_head->value);
                }
                temp_head->value = ft_strdup(t_value);
            }
            return; // 값을 업데이트하거나 유지 후 함수 종료
        }
        temp_head = temp_head->next;
    }

	new_node = malloc(sizeof(t_export));
	if (new_node == NULL)
		exit(1);
	new_node->key = ft_strdup(t_key);
	if (t_value != NULL)
        new_node->value = ft_strdup(t_value);
    else
	{
        new_node->value = NULL;
	}
	new_node->next = NULL;

	if (*p_export == NULL)
    {
        *p_export = new_node;
    }
    else
    {
        temp_head = *p_export;
        while (temp_head->next != NULL)
        {
            temp_head = temp_head->next;
        }
        temp_head->next = new_node;
    }

	// if (*p_export == NULL)
	// 	*p_export = new_node;
	// else
	// {
	// 	temp_head = *p_export;
	// 	while (temp_head->next != NULL)
	// 	{
	// 		temp_head = temp_head->next;
	// 		if (ft_strncmp(temp_head->key ,t_key, ft_strlen(t_key)) == 0 && new_node -> value != NULL)
	// 		{
	// 			temp_head->next = new_node;
	// 			return ;
	// 		}
	// 	}
	// 	temp_head->next = new_node;
	// }
}
void	divde_key_value(char **argv, t_sh *p_sh_list)
{
	int i;
	char *t_key;
	char *t_value;

	i = 1;
	while(argv[i])
	{
		new_key_value_parsing(argv[i], &t_key, &t_value);
		if (export_edgecase(t_key) == 0)
		{
			printf("invaild KEY %s\n", t_key);
			return ; //예외 처리
		}
		add_export_list2(&(p_sh_list->export_head), t_key, t_value);
		//envp_sort(&(p_sh_list->export_head));
		i ++;
	}
}

void	insert_envp(char **argv, t_sh *p_sh_list)
{
	divde_key_value(argv, p_sh_list);
}