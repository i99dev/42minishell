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

bool	is_cmd(char *cmd)
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

void	define_type(t_minishell *msh)
{
	int	i;
	int	j;

	i = 0;
	msh->command_type = (int *)malloc(sizeof(int ) * msh->command_count);
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->command_table[i][j])
		{
			if (is_cmd(msh->command_table[i][j]))
			{
				msh->command_type[i] = BUILTIN;
			}
			j++;
		}
		i++;
	}
}
