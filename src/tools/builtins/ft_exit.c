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
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_with_arg(t_minishell *msh, char **argv)
{
	if (is_string_number(argv[1]))
	{
		msh->exit_status = ft_atoi(argv[1]);
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required", 2);
		msh->exit_status = 2;
		exit(msh->exit_status);
	}
}

void	ft_exit(t_minishell *msh, int i)
{
	(void)i;
	ft_with_arg(msh, msh->cmd_table[i].cmd);
	if (msh->cmd_table[i].cmd[2])
	{
		ft_putendl_fd("exit: TOO_MANY_ARGS.", 2);
		msh->exit_status = 1;
		return ;
	}
	exit(msh->exit_status);
}
