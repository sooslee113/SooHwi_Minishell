/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:31:19 by donghwi2          #+#    #+#             */
/*   Updated: 2024/11/18 23:26:39 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// 초기 envp를 파싱하는 파일
// env, export 구조체에 각각 내용을 똑같이 채워넣음
// export 구조체는 정렬시키는 큰 함수 하나 포함됨

//기본 envp를 파싱하는 코드
void	parsing_envp(char **envp, t_sh *p_sh_list)
{
	int		i;
	int		j;
	char	*t_key;
	char	*t_value;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '\0')
		{
			if (envp[i][j] == '=')
			{
				t_key = ft_substr(envp[i], 0, j);
				t_value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
			}
			j++;
		}
		add_export_list(&(p_sh_list->export_head), t_key, t_value);
		add_env_list(&(p_sh_list->env_head), t_key, t_value);
		i++;
	}
	envp_sort(&(p_sh_list->export_head));
}
