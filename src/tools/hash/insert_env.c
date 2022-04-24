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

void	insert_new_env(t_hash_table *table, char *env)
{
	t_hash	*new;

	new = (t_hash *)malloc(sizeof(t_hash));
	new->key = find_key(env);
	new->value = find_value(env);
	new->next = NULL;
	table->table[hash(env, table->size)] = new;
	table->count++;
	free(new->key);
	free(new->value);
	free(new);
}