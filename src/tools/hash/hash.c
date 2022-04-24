/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:14:23 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 06:41:58 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * @brief This function is an implementation of the djb2 hashing algorithm.
 * link: https://github.com/i99dev/42minishell/wiki/Hash-Table
 * 
 * @param key The key to be hashed.
 * @param size  The size table of the keys.
 * @return unsigned long int 
 */

unsigned long int	hash(char *key, unsigned int size)
{
	unsigned long int	hash;
	unsigned int		i;

	hash = 5381;
	i = 0;
	while (key && key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % size);
}

t_hash_table	create_hash_table(unsigned int size)
{
	t_hash_table	table;

	table.table = (t_hash **)malloc(sizeof(t_hash *) * size);
	table.count = 0;
	table.size = size;
	return (table);
}

void	insert_hash(t_hash *hash, char *key, char *value)
{
	(void)hash;
	(void)key;
	(void)value;
}

void	delete_hash(t_hash *hash, char *key)
{
	(void)hash;
	(void)key;
}

void	print_hash(t_hash *hash)
{
	(void)hash;
}
