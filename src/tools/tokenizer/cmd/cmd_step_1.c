/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 06:17:03 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/22 06:19:18 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

bool	_check_flag_1(t_minishell *msh, int i, t_counter *cnt, char *flag)
{
	int	count;

	count = ft_strlen(flag);
	if (ft_strlen(msh->cmd_table[i]->cmd[cnt->s_i]) == count && \
		ft_strncmp(msh->cmd_table[i]->cmd[cnt->s_i], flag, count) == 0)
		return (true);
	else
		return (false);
}

void	_if_expand(t_minishell *msh, int i, t_counter *cnt)
{
	if (!ft_strncmp(msh->cmd_table[i]->cmd[cnt->s_i], "$?", 2))
	msh->cmd_table[i]->cmd[cnt->s_i] = \
	expand_cmd(msh, msh->cmd_table[i]->cmd[cnt->s_i]);
}

bool	_last_c(t_minishell *msh, int i, t_counter *cnt)
{
	if ((cnt->s_j == 0) || (ft_strncmp(msh->cmd_table[\
	i]->cmd[cnt->s_i], msh->cmd_table[i]->filename[cnt->s_j - 1], \
		ft_strlen(msh->cmd_table[i]->cmd[cnt->s_i]))))
		return (true);
	else
		return (false);
}

bool	_work_on_loop(t_minishell *msh, int i, t_counter *cnt)
{
	_if_expand(msh, i, cnt);
	if (_check_flag_1(msh, i, cnt, ">>"))
	{
		if (!_step_one_cmd(msh, i, cnt))
			return (false);
	}
	else if (_check_flag_1(msh, i, cnt, "<<"))
	{
		if (!_step_two_cmd(msh, i, cnt))
			return (false);
	}
	else if (_check_flag_1(msh, i, cnt, "<"))
	{
		if (!_step_three_cmd(msh, i, cnt))
			return (false);
	}
	else if (_check_flag_1(msh, i, cnt, ">"))
	{
		if (!_step_four_cmd(msh, i, cnt))
			return (false);
	}
	else if (_last_c(msh, i, cnt))
		_step_five_cmd(msh, i, cnt);
	return (true);
}
