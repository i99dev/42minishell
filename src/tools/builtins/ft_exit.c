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

void	ft_exit(t_minishell *msh, int i)
{
	(void)i;
	if (msh->cmd_table[i].cmd[1])
	{
		ft_putendl_fd("exit: TOO_MANY_ARGS.", 2);
		return ;
	}
	exit(0);
}
