/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:12:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 06:23:35 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_check_command_table(t_minishell *msh, int i)
{
	int		index;

	index = 0;
	msh->token_ls[i] = (t_token *)malloc(sizeof(t_token));
	while (msh->command_table[i][index])
	{
		if (ft_strncmp(msh->command_table[i][index], "<", 1) == 0)
			msh->token_ls[i]->token = ft_strdup("<");
		else if (ft_strncmp(msh->command_table[i][index], ">", 1) == 0)
			msh->token_ls[i]->token = ft_strdup(">");
		else if (ft_strncmp(msh->command_table[i][index], ">>", 2) == 0)
			msh->token_ls[i]->token = ft_strdup(">>");
		else if (ft_strncmp(msh->command_table[i][index], "<<", 2) == 0)
			msh->token_ls[i]->token = ft_strdup("<<");
		else
			free(msh->token_ls[i]);
		index++;
	}
}

void	init_command_table(t_minishell *msh)
{
	char	**tmp;
	int		table_count;
	int		i;

	i = 0;
	tmp = ft_split(msh->line, '|');
	while (tmp[i])
		i++;
	table_count = i;
	msh->command_table = (char ***)malloc(sizeof(char **) * table_count);
	msh->token_ls = (t_token **)malloc(sizeof(t_token *) * table_count);
	i = 0;
	while (tmp[i])
	{
		msh->command_table[i] = ft_split(tmp[i], ' ');
		ft_check_command_table(msh, i);
		i++;
	}
	msh->command_count = table_count;
	msh->command_table[i] = NULL;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	ft_tokenizer(t_minishell *msh)
{
	init_command_table(msh);
}
