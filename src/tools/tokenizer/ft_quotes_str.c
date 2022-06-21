/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 05:25:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/21 10:53:59 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strinsert(char *str, char *env, char *key)
{
	char	*temp;
	char	*temp2;
	int		i;
	int		j;

	(void)key;
	temp = malloc(sizeof(char) * ft_strlen(env) + ft_strlen(str) + 1);
	i = 0;
	if (str[i] == '$')
	{
		while (env[i])
		{
			temp[i] = env[i];
			i++;
			if (env[i] == '\0')
				free(env);
		}
		temp2 = ft_strdup(&str[ft_strlen(key) + 1]);
	}
	else
	{
		while (str[i] != '$' && str[i])
		{
			temp[i] = str[i];
			i++;
		}
		temp2 = ft_strdup(&str[i]);
	}
	j = 0;
	if (ft_strncmp(temp2, "$", 1))
	{
		while (temp2[j])
		{
			temp[i] = temp2[j];
			i++;
			j++;
		}
	}
	else
	{
		while (env[j])
		{
			temp[i] = env[j];
			i++;
			j++;
		}
	}
	temp[i] = '\0';
	free(temp2);
	free(str);
	return (temp);
}