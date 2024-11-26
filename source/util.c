/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:07:01 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/26 18:16:45 by sooslee          ###   ########.fr       */
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

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c =='\n')
		return (1);
	else
		return (0);
}

void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (NULL == ret)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    return (ret);
}
