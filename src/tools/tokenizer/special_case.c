/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 05:18:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/22 05:19:16 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	replace_tild(t_minishell *msh)
{
	int	i;
	int	j;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			if (ft_strncmp(msh->cmd_table[i].cmd[j], "~", 1) == 0)
				msh->cmd_table[i].cmd[j] = \
				ft_strdup(find_hash(msh->env_table, "HOME"));
			j++;
		}
		i++;
	}
}

void	ft_special_case(t_minishell *msh)
{
	int	i;
	int	j;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			if (ft_strncmp(msh->cmd_table[i].cmd[j], "~", 1) == 0)
				replace_tild(msh);
			else if (ft_strncmp(msh->cmd_table[i].cmd[j], "$", 1) == 0)
				return ;
			else if (ft_strncmp(msh->cmd_table[i].cmd[j], "$$", 3) == 0)
				return ;
			j++;
		}
		i++;
	}
}
