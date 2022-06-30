/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_handle_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 04:13:48 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/30 13:15:45 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	_step_one_qs(t_minishell *msh, t_counter *cnt, char *tmp)
{
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j][ft_strlen(\
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) - ft_strlen(tmp)] = 0;
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] = ft_strjoin(\
	msh->cmd_table[cnt->s_i]->cmd[cnt->s_j], msh->quotes[cnt->s_k]);
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

void	_step_two_qs(t_minishell *msh, t_counter *cnt, char *tmp)
{
	if (tmp[2] == 0 && ft_strlen(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]) == 2)
	{
		free(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j]);
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

bool	q_handle_s(t_minishell *msh, t_counter *cnt)
{
	char	*tmp;

	tmp = ft_strdup(ft_strchr(msh->cmd_table[cnt->s_i]->cmd[cnt->s_j] \
	+ msh->q_pos, SINGLE_QUOTE));
	if (tmp[1] && tmp[1] == SINGLE_QUOTE && ft_strlen(msh->quotes[cnt->s_k]))
	{
		_step_one_qs(msh, cnt, tmp);
		free (tmp);
		cnt->s_k += 1;
		return (true);
	}
	else if (tmp[1] && tmp[1] == SINGLE_QUOTE && \
	!ft_strlen(msh->quotes[cnt->s_k]))
	{
		_step_two_qs(msh, cnt, tmp);
		cnt->s_k += 1;
		free(tmp);
		return (true);
	}
	free(tmp);
	msh->q_pos = 0;
	return (false);
}
