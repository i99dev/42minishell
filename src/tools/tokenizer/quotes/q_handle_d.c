/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_handle_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 04:15:22 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/22 04:35:58 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	_step_one_qd(t_minishell *msh, t_counter *cnt, char *tmp)
{
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(\
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - \
	ft_strlen(tmp)] = 0;
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(\
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
	expand_cmd(msh, msh->quotes[cnt->s_k]));
	msh->q_pos = strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]);
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(\
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
	tmp + 2);
	if (!ft_strchr(tmp + 2, SINGLE_QUOTE) && \
	!ft_strchr(tmp + 2, DOUBLE_QUOTE))
	{
		msh->q_pos = 0;
		cnt->s_j++;
	}
}

void	_step_two_qd(t_minishell *msh, t_counter *cnt, char *tmp)
{
	if (tmp[2] == 0 && ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) == 2)
	{
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strdup("\t");
	}
	else
	{
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(\
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - \
		ft_strlen(tmp)] = 0;
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(\
		msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], \
		tmp + 2);
	}
}

int	q_handle_d(t_minishell *msh, t_counter *cnt)
{
	char	*tmp;

	tmp = ft_strdup(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] + \
	msh->q_pos, DOUBLE_QUOTE));
	if (tmp[1] && tmp[1] == DOUBLE_QUOTE && ft_strlen(msh->quotes[cnt->s_k]))
	{
		_step_one_qd(msh, cnt, tmp);
		free(tmp);
		cnt->s_k++;
		return (true);
	}
	else if (tmp[1] && tmp[1] == DOUBLE_QUOTE && \
	!ft_strlen(msh->quotes[cnt->s_k]))
	{
		_step_two_qd(msh, cnt, tmp);
		cnt->s_k++;
		return (true);
	}
	msh->q_pos = 0;
	free(tmp);
	return (msh->q_pos);
}
