/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/22 07:24:22 by oal-tena         ###   ########.fr       */
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

void _free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void _free_t_token(t_token **tok)
{
	int i;

	i = 0;
	while (tok[i])
	{
		free(tok[i]->token);
		free(tok[i]);
		i++;
	}
	free(tok);
}


void	ft_command_table_free(t_minishell *msh)
{
	int		i;

	i = 0;
	while (i < msh->command_count)
	{
		_free_2d_array(msh->cmd_table[i]->cmd);
		_free_2d_array(msh->cmd_table[i]->filename);
		_free_2d_array(msh->cmd_table[i]->exec_table);
		_free_t_token(msh->cmd_table[i]->tok);
		// _free_2d_array(msh->quotes);
		free(msh->cmd_table[i]);
		i++;
	}
	free(msh->cmd_table);
}

void	free_line(t_minishell *msh)
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
	if (minishell->cmd_table[0]->cmd[0])
		ft_command_table_free(minishell);
	exit(minishell->exit_status);
}
