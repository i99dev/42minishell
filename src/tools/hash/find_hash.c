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

char	*find_hash(t_hash_table *env_table, char *key)
{
	unsigned long	_hash;
	t_hash			*tmp;

	_hash = hash(key, env_table->size);
	tmp = env_table->table[_hash];
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
