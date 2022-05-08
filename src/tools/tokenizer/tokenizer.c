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

/**
 * @brief tokenizes handel it input line and split it into command table
 * 
 * @param msh 
 */

void	tokenize(t_minishell *msh)
{
	char	**line;
	int		i;

	i = 0;
	msh->token_count = 0;
	line = ft_split(msh->line, '|');
	while (line[msh->token_count])
		msh->token_count++;
	msh->token_ls = (t_token *)malloc(sizeof(char *) * msh->token_count);
	while (line[i])
	{
		msh->token_ls[i].token = ft_strdup(line[i]);
		msh->token_ls[i].type = 0;
		i++;
	}
	free(line);
}

void	init_command_table(t_minishell *msh)
{
	int		i;
	int		j;

	i = 0;
	msh->command_table = (char ***)malloc(sizeof(char **) * msh->token_count);
	while (i < msh->token_count)
	{
		j = 0;
		msh->command_table[i] = ft_split(msh->token_ls[i].token, ' ');
		while (msh->command_table[i][j])
			j++;
		i++;
	}
}

void	is_need_toknizer(t_minishell *msh)
{
	if (msh->line[0] == '\0')
		return ;
}

void	ft_tokenizer(t_minishell *msh)
{
	tokenize(msh);
	init_command_table(msh);
	is_need_toknizer(msh);
}
