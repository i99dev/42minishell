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

char	*_step_one_get_key(char *str, int *i)
{
	char	*key;

	key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (isalpha(str[*i]) || str[*i] == '?')
	{
		key[*i] = str[*i];
		if (str[(*i)++] == '?')
			break ;
	}
	key[*i] = '\0';
	return (key);
}

char	*key_last(char *str, int i, char *key)
{
	if (isdigit(str[i]) && i == 0)
	{
		free(key);
		return (ft_strdup(str + 1));
	}
	else if (isdigit(str[i]))
	{
		free(key);
		return (ft_strdup(""));
	}
	else
	{
		free(key);
		return (ft_strdup(str));
	}
	return (key);
}

char	*get_key_from_str(t_minishell *msh, char *str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = _step_one_get_key(str, &i);
	if ((key[0] != '\0' && !isdigit(str[i])))
	{
		value = find_hash(msh, msh->env_table, key);
		free(key);
		if (value && !ft_strchr(str, '?'))
			key = ft_strdup(value);
		else if (ft_strchr(str, '?'))
			key = ft_strdup(value);
		else
			key = ft_strdup("");
		key = ft_strjoin(key, &str[i]);
		free(value);
	}
	else
		key = key_last(str, i, key);
	return (key);
}

char	*_break_loop(t_minishell *msh, char *start, int *i)
{
	char	*tmp;
	char	*tmp_free;

	tmp = 0;
	while (is_parameter(&start[*i]))
	{
		while (start [*i] && start[*i] != '$')
			(*i)++;
		if (start[*i + 1] && start[*i + 1] == ' ')
		{
			if (start[*i + 2])
			{
				(*i) += 2;
				continue ;
			}
			else
				break ;
		}
		tmp_free = get_key_from_str(msh, &start[*i + 1]);
		tmp = ft_strjoin(ft_substr(start, 0, *i), tmp_free);
		free(start);
		start = tmp;
		free(tmp_free);
	}
	return (start);
}

char	*expand_cmd(t_minishell *msh, char *str)
{
	char	*start;
	int		i;
	int		len;

	start = ft_strchr(str, '$');
	if (!start)
		return (str);
	if (!start[1])
		return (str);
	i = 0 ;
	len = ft_strlen(str) - ft_strlen(start);
	start = _break_loop(msh, ft_strdup(start), &i);
	i = 0;
	str[len] = '\0';
	str = ft_strjoin(str, start);
	free(start);
	return (str);
}
