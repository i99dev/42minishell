/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 06:06:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 06:13:29 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_echo(t_minishell *msh, int i)
{
	bool	flag;
	int		j;

	flag = false;
	j = 1;
	if (msh->cmd_table[i].exec_table[1] && \
	!ft_strncmp(msh->cmd_table[i].exec_table[1], "-n", ft_strlen("-n")))
	{
		flag = true;
		j++;
	}
	while (msh->cmd_table[i].exec_table[j])
	{
		printf("%s ", msh->cmd_table[i].exec_table[j]);
		j++;
	}
	if (!flag)
		printf("\n");
}
