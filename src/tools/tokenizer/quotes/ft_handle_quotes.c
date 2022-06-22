/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 04:36:39 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/22 07:30:01 by oal-tena         ###   ########.fr       */
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

t_counter	*init_counter(t_minishell *msh)
{
	t_counter	*cnt;

	(void)msh;
	cnt = (t_counter *)malloc(sizeof(t_counter));
	cnt->s_i = 0;
	cnt->s_j = 0;
	cnt->s_k = 0;
	return (cnt);
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

bool	q_handle_all(t_minishell *msh, t_counter *cnt)
{
	t_counter	*tmp;

	tmp = init_counter(msh);
	if (ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
	msh->q_pos, DOUBLE_QUOTE))
		tmp->s_i = ft_strlen(ft_strchr(\
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + msh->q_pos, DOUBLE_QUOTE));
	if (ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
	msh->q_pos, SINGLE_QUOTE))
		tmp->s_j = ft_strlen(ft_strchr(\
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + msh->q_pos, SINGLE_QUOTE));
	if (!tmp->s_i && !tmp->s_j)
		return (false);
	else if (tmp->s_i > tmp->s_j)
	{
		if (!q_handle_d(msh, cnt))
			return (true);
	}
	else if (tmp->s_j > tmp->s_i)
	{
		if (!q_handle_s(msh, cnt))
			return (true);
	}
	return (false);
}

void	ft_handle_quotes(t_minishell *msh)
{
	t_counter	*cnt;

	cnt = init_counter(msh);
	msh->q_pos = 0;
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
