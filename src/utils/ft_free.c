/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/07 08:33:57 by Dokcer           ###   ########.fr       */
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
	if (msh->user_info)
		free(msh->user_info);
	if (msh->line)
		free(msh->line);
}

void	ft_command_table_free(char ***command_table)
{
	int	i;

	i = 0;
	while (command_table[i])
	{
		free(command_table[i]);
		i++;
	}
	free(command_table);
}

void	free_line(t_minishell *msh)
{
	if (msh->line)
	{
		free(msh->line);
		msh->line = NULL;
	}
}

void	ft_free_token_ls(t_minishell *msh)
{
	if (msh->token_ls)
	{
		free(msh->token_ls->token);
		free(msh->token_ls);
		msh->token_ls = NULL;
	}
}

void	ft_free_minishell(t_minishell *minishell)
{
	int	i;

	i = 0;
	ft_free_hash(minishell->env_table);
	ft_free_prompt(minishell);
	if (minishell->command_table)
	{
		while (minishell->command_table[i])
		{
			ft_command_table_free(minishell->command_table[i]);
			i++;
		}
	}
	if (minishell->token_ls)
		ft_free_token_ls(minishell);
	free(minishell->command_seq);
	exit(0);
}
