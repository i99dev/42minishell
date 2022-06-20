/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 06:15:15 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 06:15:15 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
exmaple of unset:
step 1 set var export $OP=I99dev
step 2 unset var unset OP note:need be without sign dollar
*/
void	ft_unset(t_minishell *msh, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (msh->cmd_table[i]->cmd[1] == NULL)
		ft_putendl_fd("unset: Too few arguments.", 2);
	else
	{
		while (msh->cmd_table[i]->cmd[1][j])
		{
			if (msh->cmd_table[i]->cmd[1][j] == '$')
				k = 1;
			j++;
		}
		if (k == 1)
			ft_putendl_fd("unset: Variable name must not contain '$'.", 2);
		else
			remove_hash(msh, msh->cmd_table[i]->cmd[1]);
	}
}
