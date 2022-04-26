/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/26 12:33:40 by oal-tena         ###   ########.fr       */
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
	if (msh->token_ls)
	{
		while (msh->token_ls[i].token)
		{
			free(&msh->token_ls[i].token);
			i++;
		}
	}
}

void	ft_command_table_free(char **command_table)
{
	int i;

	i = 0;
	while (command_table[i])
	{
		free(command_table[i]);
		i++;
	}
	free(command_table);
}

void free_line(t_minishell *msh)
{
	if (msh->line)
	{
		free(msh->line);
		msh->line = NULL;
	}
}

void ft_frre_token_ls(t_token *token_ls)
{
	int i;

	i = 0;
	while (token_ls[i].token)
	{
		free(token_ls[i].token);
		i++;
	}
	free(token_ls);
}

void	ft_free_minishell(t_minishell *minishell)
{
	ft_free_hash(minishell->env_table);
	ft_free_prompt(minishell);
	ft_command_table_free(minishell->command_table);
	free_line(minishell);
	ft_frre_token_ls(minishell->token_ls);
	free(minishell);
	exit(0);
}
