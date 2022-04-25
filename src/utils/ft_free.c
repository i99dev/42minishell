/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/25 18:52:58 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_hash(t_hash_table *table)
{
	unsigned int	i;
	unsigned long	_hash;

	i = 0;
	while (table->table[i])
	{
		_hash = hash(table->table[i]->key, table->size);
		if (table->table[_hash])
		{
			free(table->table[_hash]->key);
			free(table->table[_hash]->value);
			free(table->table[_hash]);
		}
		i++;
	}
}

void	ft_free_prompt(t_minishell *msh)
{
	int	i;

	i = 0;
	if (msh->user_info)
		free(msh->user_info);
	if (msh->line)
		free(msh->line);
	if (msh->command_table)
	{
		while (msh->command_table[i].token)
		{
			free(&msh->command_table[i].token);
			i++;
		}
	}
}

void free_token(t_token *token)
{
	int i;

	i = 0;
	while (token[i].token)
	{
		free(&token[i].token);
		i++;
	}
}

void free_line(t_minishell *msh)
{
	if (msh->line)
	{
		free(msh->line);
		msh->line = NULL;
	}
}

void	ft_free_minishell(t_minishell *minishell)
{
	ft_free_hash(minishell->env_table);
	ft_free_prompt(minishell);
	exit(0);
}
