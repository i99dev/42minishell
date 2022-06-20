/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:53 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/20 14:25:34 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/*
	Testing development!
	TODO:	make dynamic malloc
			support with pipes and redirects
			check for path errors and make error msgs
*/

int	exec_cd(t_minishell *msh, int i)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	strcat(cwd, "/");
	strcat(cwd, msh->cmd_table[i]->exec_table[1]);
	chdir(cwd);
	return (0);
}

int	exec_pwd(void)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}