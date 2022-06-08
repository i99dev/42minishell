/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:26:31 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/06 02:14:29 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * @brief we need funcation split all word wit index and next joint word
 * 
 */

bool	is_case_alph(char str)
{
	if (str >= 'a' && str <= 'z')
		return (true);
	if (str >= 'A' && str <= 'Z')
		return (true);
	if (str >= '0' && str <= '9')
		return (true);
	return (false);
}

char	*get_key_from_str(t_minishell *msh, char *str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (is_case_alph(str[i]))
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	if (key[0] != '\0')
	{
		value = find_hash(msh->env_table, key);
		if (value)
		{
			key = ft_strdup(value);
			key = ft_strjoin(key, &str[i]);
		}
		else
			key = ft_strdup("");
	}
	else
		key = ft_strdup(str);
	return (key);
}

char	*expand_cmd(t_minishell *msh, char *str)
{
	char	*tmp;
	char	*start;
	char	*res;
	int		i;
	int		len;

	start = ft_strchr(str, '$');
	if (!start)
		return (str);
	i = 0 ;
	len = ft_strlen(str) - ft_strlen(start);
	res = (char *)malloc(sizeof(char) * 1024);
	while (ft_strchr(start, '$'))
	{
		while (start[i] != '$')
			i++;
		tmp = ft_strjoin(ft_substr(start, 0, i), \
		get_key_from_str(msh, &start[i + 1]));
		start = ft_strdup(tmp);
	}
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res = ft_strjoin(res, start);
	res[ft_strlen(res)] = '\0';
	return (res);
}
