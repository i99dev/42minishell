/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/28 06:06:28 by oal-tena         ###   ########.fr       */
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
	while (array[i])
		free(array[i++]);
	free(array);
}

void free_quotes(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < msh->quote_count)
	{
		free(msh->quotes[i]);
		i++;
	}
	free(msh->quotes);
}

void	ft_command_table_free(t_minishell *msh)
{
	int		i;
	int		j;

	i = 0;
	while (i < msh->command_count)
	{
		free_2d_array(msh->cmd_table[i]->cmd);
		if (msh->cmd_table[i]->filename)
			free(msh->cmd_table[i]->filename);
		j = 0;
		while (j < msh->cmd_table[i]->token_count)
		{
			free(msh->cmd_table[i]->tok[j]->token);
			free(msh->cmd_table[i]->tok[j++]);
		}
		free(msh->cmd_table[i]->tok);
		free(msh->cmd_table[i]->exec_table);
		free(msh->cmd_table[i]);
		i++;
	}
	free(msh->quotes);
	free(msh->cmd_table);
}

void	_free_quotes(t_minishell *msh)
{
	int		i;

	i = 0;
	while (i < msh->quote_count)
	{
		free(msh->quotes[i]);
		i++;
	}
	free(msh->quotes);
}

void	_free_cmd_table(t_minishell *msh)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < msh->command_count)
	{
		while (j < msh->cmd_table[i]->cmd_count)
		{
			free(msh->cmd_table[i]->cmd[j]);
			free(msh->cmd_table[i]->exec_table[j]);
			free(msh->cmd_table[i]->filename[j]);
			k = 0;
			while (k < msh->cmd_table[i]->token_count)
				free(msh->cmd_table[i]->tok[k++]->token);
			free(msh->cmd_table[i]->tok);
			free(msh->cmd_table[i]);
			j++;
		}
		i++;
	}
	free(msh->cmd_table);
}

void	ft_free_minishell(t_minishell *minishell)
{
	ft_free_hash(minishell->env_table);
	ft_free_prompt(minishell);
	_free_cmd_table(minishell);
	_free_quotes(minishell);
	ft_command_table_free(minishell);
	exit(minishell->exit_status);
}
