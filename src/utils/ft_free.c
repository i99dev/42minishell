/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 12:40:46 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_hash(t_hash_table *env_table)
{
	unsigned int	i;

	i = 0;
	while (i < env_table->size)
	{
		if (env_table->table[i])
		{
			free(env_table->table[i]->key);
			free(env_table->table[i]->value);
			free(env_table->table[i]);
		}
		i++;
	}
	free(env_table->table);
	free(env_table);
}

void	ft_free_minishell(t_minishell *minishell)
{
	ft_free_hash(minishell->env_table);
}