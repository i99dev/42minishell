/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:25:29 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 05:02:48 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_io_filename(t_minishell *msh, int i, char *token, int index)
{
	if (ft_strlen(msh->cmd_table[i].cmd[index]) == 1)
	{
		printf("redirect with space\n");
		return (ft_strdup(msh->cmd_table[i].cmd[index + 1]));
	}
	else
		return (ft_strdup(check_file_name(msh->cmd_table[i].cmd, token)));
}

void	count_token(t_minishell *msh, int i)
{
	int		index;

	index = 0;
	msh->cmd_table[i].token_count = 0;
	while (msh->cmd_table[i].cmd[index])
	{
		if (ft_strchr(msh->cmd_table[i].cmd[index], '<') != NULL)
		{
			msh->cmd_table[i].token_count++;
		}
		else if (ft_strchr(msh->cmd_table[i].cmd[index], '>') != NULL)
		{
			msh->cmd_table[i].token_count++;
		}
		index++;
	}
	msh->cmd_table[i].tok = (t_token *)malloc(sizeof(t_token ) * \
	msh->cmd_table[i].token_count);
	msh->cmd_table[i].filename = (char **)malloc(sizeof(char *) * msh->cmd_table[i].token_count);
}

static int	tk_handle_redirect_in(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
	//msh->token_ls[i][*j] = (t_token *)malloc(sizeof(t_token));
	msh->cmd_table[i].tok[*j].token = ft_strdup("<");
	msh->cmd_table[i].filename[*j] = \
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
	//msh->cmd_table[i].tok[i][*j] = (t_token *)malloc(sizeof(t_token));
	msh->cmd_table[i].tok[*j].token = ft_strdup(">");
	msh->cmd_table[i].filename[*j] = \
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
	while (msh->cmd_table[i].cmd[index] && j < msh->cmd_table[i].token_count)
	{
		if (ft_strncmp(msh->cmd_table[i].cmd[index], ">>", 2) == 0)
			msh->cmd_table[i].tok[j].token = ft_strdup(">>");
		else if (ft_strncmp(msh->cmd_table[i].cmd[index], "<<", 2) == 0)
			msh->cmd_table[i].tok[j].token = ft_strdup("<<");
		else if (ft_strchr(msh->cmd_table[i].cmd[index], '<') != NULL)
			wordindex += tk_handle_redirect_in(msh, i, &j, index);
		else if (ft_strchr(msh->cmd_table[i].cmd[index], '>') != NULL)
			wordindex += tk_handle_redirect_out(msh, i, &j, index);
		/*check for comamand token and set token, and make type -1*/
		index++;
	}
	//set_command_table();
	if (msh->cmd_table[i].token_count > 0)
		msh->cmd_table[i].cmd[wordindex] = NULL;
	msh->cmd_table[i].exec_table=msh->cmd_table[i].cmd;
}
