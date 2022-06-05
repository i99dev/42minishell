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
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			if (ft_strncmp(msh->cmd_table[i].cmd[j], "~", 1) == 0)
			{
				tmp = find_hash(msh->env_table, "HOME");
				if (tmp)
					msh->cmd_table[i].cmd[j] = ft_strdup(tmp);
				else
					msh->cmd_table[i].cmd[j] = ft_strdup("/");
			}
			j++;
		}
		i++;
	}
}

void	handle_sign_dollar(t_minishell *msh)
{
	int		i;
	int		j;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			if (ft_strchr(msh->cmd_table[i].cmd[j], '$'))
				msh->cmd_table[i].cmd[j] = expand_parameters(msh, \
				msh->cmd_table[i].cmd[j]);
			j++;
		}
		i++;
	}
}

void handle_double_dollar(t_minishell *msh)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			if (msh->cmd_table[i].cmd[j][0] == '$' && \
			msh->cmd_table[i].cmd[j][1] == '$')
			{
				tmp = find_hash(msh->env_table, msh->cmd_table[i].cmd[j] + 2);
				if (tmp)
					msh->cmd_table[i].cmd[j] = ft_itoa(getpid());
				else
					msh->cmd_table[i].cmd[j] = ft_strdup("");
			}
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
			else if (ft_strncmp(msh->cmd_table[i].cmd[j], "$$", 3) == 0)
				handle_double_dollar(msh);
			else if (ft_strncmp(msh->cmd_table[i].cmd[j], "$", 1) == 0)
				handle_sign_dollar(msh);
			j++;
		}
		i++;
	}
}
