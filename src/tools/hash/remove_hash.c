/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 09:50:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/26 09:51:25 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	remove_hash(t_minishell *msh, char *key)
{
	unsigned int	i;

	i = hash(key, msh->env_table->size);
	if (msh->env_table->table[i])
	{
		free(msh->env_table->table[i]->key);
		free(msh->env_table->table[i]->value);
		msh->env_table->table[i] = NULL;
	}
	//msh->env = env2d(msh->env_table);
}
