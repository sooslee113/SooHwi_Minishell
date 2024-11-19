/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:45:12 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/19 00:00:25 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"////////11.18 만들다 만 split_2 

int	ft_count_word(char const *s)
{
	int	i;
	int	word_num;

	i = 0;
	word_num = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' && s[i] != '\0')
			i++;
		if (s[i] != ' ' && s[i] != '\0')
			word_num++;
		while (s[i] != ' ' && s[i] != '\0')
			i++;
	}
	return (word_num);
}

char	**ft_malloc(char const *str)
{
	int		i;
	char	**dstr;

	i = ft_count_word(str);
	dstr = malloc(sizeof(*dstr) * (i + 1));
	if (dstr == 0)
		return (0);
	return (dstr);
}

int	ft_count_next(char const *str, int i)
{
	int	cnt;

	cnt = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	while (str[i] != ' ' && str[i] != '\0' )
	{
		cnt++;
		i++;
	}
	return (cnt);
}

char	**ft_free(char **dstr, int i)
{
	int	j;

	j = 0;
	while (j < i && dstr[j] != 0)
	{
		free(dstr[j]);
		j++;
	}
	free(dstr);
	return (NULL);
}

char	**ft_split_2(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	**dstr;

	k = 0;
	i = -1;
	dstr = ft_malloc(s);
	if (dstr == NULL)
		return (NULL);
	while (++i < ft_count_word(s))
	{
		j = 0;
		dstr[i] = malloc(ft_count_next(s, k) + 1);
		if (dstr[i] == NULL)
			return (ft_free(dstr, i));
		while (s[k] != '\0' && s[k] == ' ')
			k++;
		while (s[k] != '\0' && s[k] != ' ')
			dstr[i][j++] = s[k++];
		dstr[i][j] = '\0';
	}
	dstr[i] = 0;
	return (dstr);
}