/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:16:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/21 03:17:15 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/*
t_hash	add_new_env(char *key, char *value)
{
	t_hash	new_env;

	new_env.key = key;
	new_env.value = value;
	return (new_env);
}
*/

void	update_hash(t_minishell *msh, char *key, char *value)
{
	unsigned int	i;

	i = hash(key, msh->env_table->size);
	if (msh->env_table->table[i])
	{
		free(msh->env_table->table[i]->key);
		free(msh->env_table->table[i]->value);
		msh->env_table->table[i]->key = ft_strdup(key);
		msh->env_table->table[i]->value = ft_strdup(value);
	}
	else
	{
		msh->env_table->table[i] = malloc(sizeof(t_hash));
		msh->env_table->table[i]->key = ft_strdup(key);
		msh->env_table->table[i]->value = ft_strdup(value);
		msh->env_table->count++;
	}
	free(msh->env);
	msh->env = env2d(msh->env_table);
}
