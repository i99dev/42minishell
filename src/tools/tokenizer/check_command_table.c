/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:25:29 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/23 03:43:34 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_io_filename(t_minishell *msh, int i, char *token, int index)
{
	if (ft_strlen(msh->command_table[i][index]) == 1)
	{
		printf("redirect with space\n");
		return (ft_strdup(msh->command_table[i][index + 1]));
	}
	else
		return (ft_strdup(check_file_name(msh->command_table[i], token)));
}

void	count_token(t_minishell *msh, int i)
{
	int		index;

	index = 0;
	msh->token_count[i] = 0;
	while (msh->command_table[i][index])
	{
		if (ft_strchr(msh->command_table[i][index], '<') != NULL)
		{
			msh->token_count[i]++;
		}
		else if (ft_strchr(msh->command_table[i][index], '>') != NULL)
		{
			msh->token_count[i]++;
		}
		index++;
	}
	msh->token_ls[i] = (t_token **)malloc(sizeof(t_token *) * \
	msh->token_count[i]);
	msh->filename_ls[i] = (char **)malloc(sizeof(char *) * msh->token_count[i]);
}

static int	tk_handle_redirect_in(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
	msh->token_ls[i][*j] = (t_token *)malloc(sizeof(t_token));
	msh->token_ls[i][*j]->token = ft_strdup("<");
	msh->filename_ls[i][*j] = \
	get_io_filename(msh, i, "<", index);
	(*j)++;
	if (*j == 1)
		wordindex = index;
	return (wordindex);
}

static int	tk_handle_redirect_out(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
	msh->token_ls[i][*j] = (t_token *)malloc(sizeof(t_token));
	msh->token_ls[i][*j]->token = ft_strdup(">");
	msh->filename_ls[i][*j] = \
	get_io_filename(msh, i, ">", index);
	(*j)++;
	if (*j == 1)
		wordindex = index;
	return (wordindex);
}

void	check_command_table(t_minishell *msh, int i)
{
	int		index;
	int		wordindex;
	int		j;

	index = 0;
	j = 0;
	wordindex = 0;
	count_token(msh, i);
	while (msh->command_table[i][index] && j < msh->token_count[i])
	{
		if (ft_strncmp(msh->command_table[i][index], ">>", 2) == 0)
			msh->token_ls[i][j]->token = ft_strdup(">>");
		else if (ft_strncmp(msh->command_table[i][index], "<<", 2) == 0)
			msh->token_ls[i][j]->token = ft_strdup("<<");
		else if (ft_strchr(msh->command_table[i][index], '<') != NULL)
			wordindex += tk_handle_redirect_in(msh, i, &j, index);
		else if (ft_strchr(msh->command_table[i][index], '>') != NULL)
			wordindex += tk_handle_redirect_out(msh, i, &j, index);
		index++;
	}
	if (msh->token_count[i] > 0)
		msh->command_table[i][wordindex] = NULL;
}
