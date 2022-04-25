/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 09:38:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 09:40:35 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*find_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	return (key);
}

char	*find_value(char *env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	j = i + 1;
	while (env[i])
		i++;
	value = ft_substr(env, j, i);
	return (value);
}

void	insert_hash(t_hash_table *table, char *env)
{
	char			*key;
	char			*value;
	unsigned long	_hash;

	key = find_key(env);
	value = find_value(env);
	_hash = hash(key, table->size);
	if (table->table[_hash])
	{
		free(key);
		free(value);
		return ;
	}
	table->table[_hash] = malloc(sizeof(t_hash));
	table->table[_hash]->key = key;
	table->table[_hash]->value = value;
}
