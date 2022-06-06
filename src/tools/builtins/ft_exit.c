/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:08:07 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/26 10:08:19 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	is_string_number(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_with_arg(t_minishell *msh, char **argv)
{
	if (argv[1] && is_string_number(argv[1]))
	{
		error_message(msh, "exit: numeric argument required", 2);
	}
}

void	ft_exit(t_minishell *msh, int i)
{
	(void)i;
	ft_with_arg(msh, msh->cmd_table[i].cmd);
	if (msh->command_count > 1)
	{
		error_message(msh, "exit: too many arguments", 1);
		msh->exit_status = 1;
		return ;
	}
	exit(msh->exit_status);
}
