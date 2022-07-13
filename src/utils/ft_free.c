/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/13 09:05:26 by Dokcer           ###   ########.fr       */
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

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
}

void	free_token(t_cmdt *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->token_count)
	{
		free(cmd->tok[i]->token);
		free(cmd->tok[i]);
		i++;
	}
	cmd->token_count = 0;
	free(cmd->tok);
}

void	free_quotes(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < msh->quote_count)
		free(msh->quotes[i++]);
	if (msh->quote_count)
		free(msh->quotes);
	msh->quote_count = 0;
}

void	ft_command_table_free(t_minishell *msh)
{
	int		i;

	i = 0;
	while (i < msh->command_count)
	{
		free_2d_array(msh->cmd_table[i]->cmd);
		if (msh->cmd_table[i]->is_filename)
			free_2d_array(msh->cmd_table[i]->filename);
		//free(msh->cmd_table[i]->filename);
		free_token(msh->cmd_table[i]);
		free(msh->cmd_table[i]->exec_table);
		free(msh->cmd_table[i]);
		i++;
	}
	free_quotes(msh);
	free(msh->cmd_table);
}

void	ft_free_minishell(t_minishell *minishell)
{
	ft_free_hash(minishell->env_table);
	exit(minishell->exit_status);
}
