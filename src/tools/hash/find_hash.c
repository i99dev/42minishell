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

/**
 * @brief exmaple if user type echo $USER this function will return USER
 * 
 * @param env_table  this table get from structer env under the key "env_table"
 * @param key its the key we want to find exmaple "HOME" or "PWD"
 * @return char* value of the key
 */

char	*find_hash(t_minishell *msh,t_hash_table *env_table, char *key)
{
	unsigned long	_hash;
	t_hash			*tmp;
	unsigned int				i;

	if(key && key[0]=='?')
		return ft_itoa(msh->exit_status);
	i = 0;
	while (i < env_table->size)
	{
		if (env_table->table[i] && !ft_strncmp(env_table->table[i]->key, key,ft_strlen(env_table->table[i]->key)))
		{
			_hash = hash(key, env_table->size);
			tmp = env_table->table[_hash];
			if (tmp)
				return (tmp->value);
		}
		i++;
	}
	return (NULL);
}
