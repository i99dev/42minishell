/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/22 09:56:07 by Dokcer           ###   ########.fr       */
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
	if (msh->line)
		free(msh->line);
}

void	ft_command_table_free(t_minishell *msh)
{
	int		i;
	int		j;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->command_table[i][j])
		{
			free(msh->command_table[i][j]);
			j++;
		}
		free(msh->command_table[i]);
		i++;
	}
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
	(void)msh;
	/*
	int		i;


	i = 0;
	while (i < msh->command_count)
	{
		if (msh->token_ls[i])
		{
			free(msh->token_ls[i]->token);
		}
		free(msh->token_ls[i]);
		i++;
	}
	free(msh->token_ls);*/
}

void	ft_free_minishell(t_minishell *minishell)
{
	ft_free_hash(minishell->env_table);
	ft_free_prompt(minishell);
	if (minishell->command_table)
		ft_command_table_free(minishell);
	if (minishell->token_ls)
		ft_free_token_ls(minishell);
	exit(0);
}
