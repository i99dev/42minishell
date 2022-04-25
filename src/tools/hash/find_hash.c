/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:17:22 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/25 08:18:10 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	find_hash(t_hash_table *table, char *key)
{
	unsigned long	_hash;
	t_hash			*temp_hash;

	_hash = hash(key, table->size);
	temp_hash = table->table[_hash];
	while (temp_hash)
	{
		if (ft_strncmp(temp_hash->key, key, ft_strlen(key)) == 0)
			break ;
		temp_hash = temp_hash->next;
	}
	if (temp_hash)
		ft_putstr_fd(temp_hash->value, 1);
	else
		ft_putstr_fd("", 1);
}
