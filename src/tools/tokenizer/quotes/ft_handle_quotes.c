/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 04:36:39 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/22 04:00:27 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

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

int	q_handle_d(t_minishell *msh, t_counter *cnt)
{
	char	*tmp;

	tmp = ft_strdup(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
	msh->q_pos, DOUBLE_QUOTE));
	if (tmp[1] && tmp[1] == DOUBLE_QUOTE && ft_strlen(msh->quotes[cnt->s_k]))
	{
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - \
		ft_strlen(tmp)] = 0;
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
		expand_cmd(msh, msh->quotes[cnt->s_k]));
		msh->q_pos = strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]);
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
		tmp + 2);
		if (!ft_strchr(tmp + 2, SINGLE_QUOTE) && \
		!ft_strchr(tmp + 2, DOUBLE_QUOTE))
		{
			msh->q_pos = 0;
			cnt->s_j++;
		}
		free(tmp);
		cnt->s_k++;
		return (true);
	}
	else if (tmp[1] && tmp[1] == DOUBLE_QUOTE && !ft_strlen(msh->quotes[cnt->s_k]))
	{
		if (tmp[2] == 0 && ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) == 2)
		{
			msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strdup("\t");
		}
		else
		{
			msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - \
			ft_strlen(tmp)] = 0;
			msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
			tmp + 2);
		}
		cnt->s_k++;
		return (true);
	}
	msh->q_pos = 0;
	free(tmp);
	return (msh->q_pos);
}

bool	q_handle_s(t_minishell *msh, t_counter *cnt)
{
	char	*tmp;

	tmp = ft_strdup(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] \
	+ msh->q_pos, SINGLE_QUOTE));
	if (tmp[1] && tmp[1] == SINGLE_QUOTE && ft_strlen(msh->quotes[cnt->s_k]))
	{
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - \
		ft_strlen(tmp)] = 0;
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
			msh->quotes[cnt->s_k]);
		msh->q_pos = strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]);
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
		tmp + 2);
		if (!ft_strchr(tmp + 2, SINGLE_QUOTE) && \
		!ft_strchr(tmp + 2, DOUBLE_QUOTE))
		{
			msh->q_pos = 0;
			cnt->s_j++;
		}
		free (tmp);
		cnt->s_k += 1;
		return (true);
	}
	else if (tmp[1] && tmp[1] == SINGLE_QUOTE && !ft_strlen(msh->quotes[cnt->s_k]))
	{
		if (tmp[2] == 0 && ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) == 2)
			msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strdup("\t");
		else
		{
			msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - \
			ft_strlen(tmp)] = 0;
			msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
		tmp + 2);
		}
		cnt->s_k += 1;
		return (true);
	}
	msh->q_pos = 0;
	return (false);
}

bool	q_handle_all(t_minishell *msh, t_counter *cnt)
{
	int	tmp1;
	int	tmp2;

	tmp1 = 0;
	tmp2 = 0;
	if (ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
	msh->q_pos, DOUBLE_QUOTE))
		tmp1 = ft_strlen(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
		msh->q_pos, DOUBLE_QUOTE));
	if (ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
	msh->q_pos, SINGLE_QUOTE))
		tmp2 = ft_strlen(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
		msh->q_pos, SINGLE_QUOTE));
	if (!tmp1 && !tmp2)
		return (false);
	else if (tmp1 > tmp2)
	{
		if (!q_handle_d(msh, cnt))
			return (true);
	}
	else if (tmp2 > tmp1)
	{
		if (!q_handle_s(msh, cnt))
			return (true);
	}
	return (false);
}

t_counter	*init_counter(t_minishell *msh)
{
	t_counter	*cnt;

	msh->q_pos = 0;
	cnt = (t_counter *)malloc(sizeof(t_counter));
	cnt->s_i = 0;
	cnt->s_j = 0;
	cnt->s_k = 0;
	return (cnt);
}

void	ft_handle_quotes(t_minishell *msh)
{
	t_counter	*cnt;

	cnt = init_counter(msh);
	while (cnt->s_i < msh->command_count)
	{
		cnt->s_j = 0;
		while (msh->cmd_table[cnt->s_i]->cmd[cnt->s_j])
		{
			msh->q_pos = 0;
			while (cnt->s_k < msh->quote_count && \
			(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
			msh->q_pos, DOUBLE_QUOTE) || \
			ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
			msh->q_pos, SINGLE_QUOTE)))
			{
				if (q_handle_all(msh, cnt))
					break ;
			}
			cnt->s_j++;
			if (cnt->s_j > msh->cmd_table[cnt->s_i]->cmd_count)
				break ;
		}
		cnt->s_i++;
	}
}
