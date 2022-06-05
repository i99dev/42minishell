/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 04:36:39 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/05 17:55:58 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	is_case(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

char	*get_key(char *str)
{
	char	*key;
	int		i;
	int		j;

	i = 0;
	j = 0;
	key = malloc(sizeof(char) * 200);
	while (str[i] != '$')
		i++;
	i++;
	while (is_case(str[i]))
	{
		key[j] = str[i];
		i++;
		j++;
	}
	key[j] = 0;
	return (key);
}

char	*expand_parameters(t_minishell *msh, char *str)
{
	int		i;
	char	*temp_quote;
	char	*temp_param;
	char   *key;

	i = 0;
	temp_quote = ft_strchr(ft_strdup(str), '$');
	while (temp_quote)
	{
		i = 0;
		while (temp_quote[i] && temp_quote[i] != ' ' \
		&& temp_quote[i] != SINGLE_QUOTE)
			i++;
		temp_param = malloc(sizeof(char) * i);
		key = get_key(temp_quote);
		str = ft_strdup(ft_strinsert(str, ft_strdup(find_hash(msh->env_table, key)), key));
		free(temp_param);
		temp_quote++;
		temp_quote = ft_strchr(temp_quote, '$');
	}
	if (ft_strncmp(str, "$", 1) == 0)
		str = expand_parameters(msh, str);
	return (str);
}

bool	q_handle_d(t_minishell *msh, int i, int j, int *k)
{
	char	*tmp;

	tmp = ft_strdup(ft_strchr(msh->cmd_table[i].cmd[j], DOUBLE_QUOTE));
	if (tmp[1] && tmp[1] == DOUBLE_QUOTE)
	{
		msh->cmd_table[i].cmd[j][ft_strlen(msh->cmd_table[i].cmd[j]) - \
		ft_strlen(tmp)] = 0;
		msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j], \
		expand_parameters(msh, msh->quotes[*k]));
		msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j], \
		tmp + 2);
		free(tmp);
		*k += 1;
		return (true);
	}
	else
		return (false);
}

bool	q_handle_s(t_minishell *msh, int i, int j, int *k)
{
	char	*tmp;

	tmp = ft_strdup(ft_strchr(msh->cmd_table[i].cmd[j], SINGLE_QUOTE));
	if (tmp[1] && tmp[1] == SINGLE_QUOTE)
	{
		msh->cmd_table[i].cmd[j][ft_strlen(msh->cmd_table[i].cmd[j]) - \
		ft_strlen(tmp)] = 0;
		if (msh->quotes)
			msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j], \
			msh->quotes[*k]);
		msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j], \
		tmp + 2);
		free (tmp);
		*k += 1;
		return (true);
	}
	else
		return (false);
}

bool	q_handle_all(t_minishell *msh, int i, int j, int *k)
{
	if (ft_strchr(msh->cmd_table[i].cmd[j], DOUBLE_QUOTE))
	{
		if (!q_handle_d(msh, i, j, k))
			return (true);
	}
	else if (ft_strchr(msh->cmd_table[i].cmd[j], SINGLE_QUOTE))
	{
		if (!q_handle_s(msh, i, j, k))
			return (true);
	}
	return (false);
}

void	ft_handle_quotes(t_minishell *msh)
{
	int		i;
	int		j;
	int		k;
	bool	b;

	k = 0;
	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			while (k < msh->quote_count && \
			(ft_strchr(msh->cmd_table[i].cmd[j], DOUBLE_QUOTE) || \
			ft_strchr(msh->cmd_table[i].cmd[j], SINGLE_QUOTE)))
			{
				b = q_handle_all(msh, i, j, &k);
				if (b)
					break ;
			}
			j++;
		}
		i++;
	}
}
