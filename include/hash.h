/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:37:44 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 06:38:11 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

typedef struct s_hash
{
	char			*key;
	char			*value;
	struct s_hash	*next;
}					t_hash;

typedef struct hash_table
{
	t_hash			**table;
	unsigned int	count;
	unsigned int	size;
}					t_hash_table;

unsigned long int	hash(char *key, unsigned int size);
t_hash_table		*create_hash_table(unsigned int size);
void				insert_new_env(t_hash_table *table, char *env);
void				print_hash(t_hash_table *table);

#endif