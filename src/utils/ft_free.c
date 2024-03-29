/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:39:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/26 12:53:44 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_hash(t_hash_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->size)
	{
		if (table->table[i])
		{
			free(table->table[i]->key);
			free(table->table[i]->value);
			free(table->table[i]);
		}
		i++;
	}
	free(table->table);
	free(table);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (1)
		{
			if (array[i])
			{
				free(array[i++]);
			}
			else
				break ;
		}
	}
	free(array);
}

void	free_token(t_cmdt *cmd)
{
	int	i;

	i = 0;
	if (cmd->tok)
	{
		while (1)
		{
			if (cmd->tok[i])
			{
				free(cmd->tok[i]);
				i++;
			}
			else
			{
				break ;
			}
		}
	}
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
		if (msh->cmd_table[i]->filename)
			free_2d_array(msh->cmd_table[i]->filename);
		free_token(msh->cmd_table[i]);
		free(msh->cmd_table[i]->exec_table);
		free(msh->cmd_table[i]);
		i++;
	}
	free_quotes(msh);
	free(msh->cmd_table);
}
