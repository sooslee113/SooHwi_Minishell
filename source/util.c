/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:07:01 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/19 01:08:21 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//libft 스핀오프

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (*ss1 != '\0' || *ss2 != '\0')
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
		i++;
	}
	return (0);
}
// export_head로 환경변수 출력하기
void	print_export_list(t_export *export_head)
{
	t_export *temp = export_head;

	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
//env 함수 출력하기
void	print_env_list(t_env *env_head)
{
	t_env *temp = env_head;

	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}