/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:32:21 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 06:12:42 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(t_minishell *msh, int i)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	strcat(cwd, "/");
	strcat(cwd, msh->cmd_table[i].exec_table[1]);
	chdir(cwd);
	return (0);
}
