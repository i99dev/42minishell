/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:44:20 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 10:44:39 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	print_hash(t_hash_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->size)
	{
		if (table->table[i])
		{
			printf("|%s=%s|\n", table->table[i]->key, table->table[i]->value);
		}
		i++;
	}
}