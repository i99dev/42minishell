/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_step_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 06:27:59 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/23 10:17:26 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

bool	_step_one_cmd(t_minishell *msh, int i, t_counter *cnt)
{
	if (!msh->cmd_table[i]->cmd[cnt->s_i + 1])
		return (false);
	//msh->cmd_table[i]->tok[cnt->s_j] = (t_token *)malloc(sizeof(t_token));
	msh->cmd_table[i]->tok[cnt->s_j]->token = ">>";
	msh->cmd_table[i]->filename[cnt->s_j] = \
		get_io_filename(msh, i, ">>", cnt->s_i);
	cnt->s_j++;
	return (true);
}

bool	_step_two_cmd(t_minishell *msh, int i, t_counter *cnt)
{
	if (!msh->cmd_table[i]->cmd[cnt->s_i + 1])
		return (false);
	//msh->cmd_table[i]->tok[cnt->s_j] = (t_token *)malloc(sizeof(t_token));
	msh->cmd_table[i]->tok[cnt->s_j]->token = "<<";
	msh->cmd_table[i]->filename[cnt->s_j] = \
	get_io_filename(msh, i, "<<", cnt->s_i);
	cnt->s_j++;
	return (true);
}

bool	_step_three_cmd(t_minishell *msh, int i, t_counter *cnt)
{
	if (!msh->cmd_table[i]->cmd[cnt->s_i + 1])
		return (false);
	tk_handle_redirect_in(msh, i, &cnt->s_j, cnt->s_i);
	return (true);
}

bool	_step_four_cmd(t_minishell *msh, int i, t_counter *cnt)
{
	if (!msh->cmd_table[i]->cmd[cnt->s_i + 1])
		return (false);
	tk_handle_redirect_out(msh, i, &cnt->s_j, cnt->s_i);
	return (true);
}

void	_step_five_cmd(t_minishell *msh, int i, t_counter *cnt)
{
	if (msh->cmd_table[i]->cmd[cnt->s_i])
	{
		if (msh->cmd_table[i]->cmd[cnt->s_i][0] == '\r')
		msh->cmd_table[i]->cmd[cnt->s_i] = \
		ft_strtrim(msh->cmd_table[i]->cmd[cnt->s_i], "\r");
		msh->cmd_table[i]->exec_table[cnt->s_k] = \
		msh->cmd_table[i]->cmd[cnt->s_i];
		cnt->s_k++;
	}
}
