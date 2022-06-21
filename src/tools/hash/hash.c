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

t_hash_table	*init_table(char **env)
{
	t_hash_table		*table;
	int					len;

	len = 0;
	while (env[len])
		len++;
	table = create_hash_table(50000);
	table->count = 0;
	len = 0;
	while (env[len])
	{
		insert_hash(table, env[len]);
		len++;
	}
	return (table);
}

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

t_hash_table	*create_hash_table(unsigned int size)
{
	t_hash_table	*env_table;
	unsigned int	i;

	i = 0;
	env_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	env_table->table = (t_hash **)malloc(sizeof(t_hash *) * size);
	while (i < size)
	{
		env_table->table[i] = NULL;
		i++;
	}
	env_table->size = size;
	return (env_table);
}

char	**env2d(t_hash_table *env_table)
{
	char			**env;
	unsigned int	i;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (env_table->count + 1));
	while (i < env_table->count)
	{
		while (env_table->table[i])
		{
			env[i] = ft_strjoin(ft_strdup(env_table->table[i]->key), "=");
			env[i] = ft_strjoin(env[i], env_table->table[i]->value);
			env_table->table[i] = env_table->table[i]->next;
		}
			i++;
	}
	env[i] = NULL;
	return (env);
}
