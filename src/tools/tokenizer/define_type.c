/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:37:19 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/16 08:40:23 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 2) == 0 || ft_strncmp(cmd, "echo", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 5) == 0 || ft_strncmp(cmd, "env", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 3) == 0 || ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (true);
	return (false);
}

bool	is_operator(char *cmd)
{
	if (ft_strncmp(cmd, ">", 1) == 0 || ft_strncmp(cmd, "<", 1) == 0)
		return (true);
	else if (ft_strncmp(cmd, ">>", 2) == 0 || ft_strncmp(cmd, "<<", 2) == 0)
		return (true);
	return (false);
}

bool	is_her_doc(char *cmd)
{
	if (ft_strncmp(cmd, "<<", 2) == 0)
		return (true);
	return (false);
}

void	define_type(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < msh->command_count)
	{
		msh->cmd_table[i].command_type  = 0;
			if (is_builtin(msh->cmd_table[i].exec_table[0]))
				msh->cmd_table[i].command_type = BUILTIN;
			else if (is_operator(msh->cmd_table[i].exec_table[0]))
			{
				if (is_her_doc(msh->cmd_table[i].exec_table[0]))
					msh->cmd_table[i].command_type = HER_DOC;
				else
					msh->cmd_table[i].command_type = OPERATOR;
			}
			else if (msh->cmd_table[i].exec_table[0])
				msh->cmd_table[i].command_type = PIPE;
		i++;
	}
}
