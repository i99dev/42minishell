/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:25:29 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/06 16:17:00 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


char	*get_io_filename(t_minishell *msh, int i, char *token, int index)
{
	if (is_token(msh->cmd_table[i].cmd[index]) && \
	ft_strlen(msh->cmd_table[i].cmd[index]) <= 2)
	{
		//printf("redirect with space\n");
		return (ft_strdup(msh->cmd_table[i].cmd[index + 1]));
	}
	else
		return (ft_strdup(check_file_name(msh->cmd_table[i].cmd, token, index)));
}

void	alloc_cmd(t_minishell *msh, int i, char ***exec, t_token **tok, char ***filename)
{
	*exec = (char **)malloc(sizeof(char *) * (msh->cmd_table[i].arg_count + 1));
	*tok = (t_token *)malloc(sizeof(t_token) * msh->cmd_table[i].token_count);
	*filename = (char **)malloc(sizeof(char *) * msh->cmd_table[i].token_count);
}

bool	is_token(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (true);
	else if (ft_strchr(str, '<') != NULL)
		return (true);
	else if (ft_strchr(str, '>') != NULL)
		return (true);
	return (false);
}

void	count_token(t_minishell *msh, int i)
{
	int		index;

	index = 0;
	msh->cmd_table[i].token_count = 0;
	msh->cmd_table[i].arg_count = 0;
	while (msh->cmd_table[i].cmd[index])
	{
		if (is_token(msh->cmd_table[i].cmd[index]) && \
			ft_strlen(msh->cmd_table[i].cmd[index]) <= 2)
		{
			msh->cmd_table[i].token_count++;
			if (msh->cmd_table[i].cmd[index + 1] && \
				!is_token(msh->cmd_table[i].cmd[index + 1]))
			{
				index += 2;
				continue ;
			}
		}
		else if (is_token(msh->cmd_table[i].cmd[index]))
			msh->cmd_table[i].token_count++;
		else
			msh->cmd_table[i].arg_count++;
		index++;
	}
	//printf("token count:%d\narg count:%d",msh->cmd_table[i].token_count,msh->cmd_table[i].arg_count);
	alloc_cmd(msh,i,&msh->cmd_table[i].exec_table, &msh->cmd_table[i].tok, &msh->cmd_table[i].filename);
	msh->cmd_table[i].exec_table[msh->cmd_table[i].arg_count] = NULL;
}

static int	tk_handle_redirect_in(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
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
	int		j;
	int		k;

	index = 0;
	j = 0;
	k = 0;
	count_token(msh, i);
	while (msh->cmd_table[i].cmd[index])
	{
		if (!ft_strncmp(msh->cmd_table[i].cmd[index], "$?", 2))
		{
			free(msh->cmd_table[i].cmd[index]);
			msh->cmd_table[i].cmd[index] = ft_itoa(msh->exit_status);
			msh->exit_status = 0;
		}
		if (msh->cmd_table[i].cmd[index] && ft_strncmp(msh->cmd_table[i].cmd[index], ">>", 2) == 0)
		{
			msh->cmd_table[i].tok[j].token = ft_strdup(">>");
			msh->cmd_table[i].filename[j] = \
				get_io_filename(msh, i, ">>", index);
			j++;
		}
		else if (msh->cmd_table[i].cmd[index] && ft_strncmp(msh->cmd_table[i].cmd[index], "<<", 2) == 0)
		{
			msh->cmd_table[i].tok[j].token = ft_strdup("<<");
			msh->cmd_table[i].filename[j] = \
			get_io_filename(msh, i, "<<", index);
			j++;
		}
		else if (msh->cmd_table[i].cmd[index] && ft_strchr(msh->cmd_table[i].cmd[index], '<') != NULL)
			tk_handle_redirect_in(msh, i, &j, index);
		else if (msh->cmd_table[i].cmd[index] && ft_strchr(msh->cmd_table[i].cmd[index], '>') != NULL)
			tk_handle_redirect_out(msh, i, &j, index);
		else if ((j == 0) || (ft_strncmp(msh->cmd_table[i].cmd[index], \
			msh->cmd_table[i].filename[j - 1], \
			ft_strlen(msh->cmd_table[i].cmd[index]))))
		{
			if(msh->cmd_table[i].cmd[index])
			{
			msh->cmd_table[i].exec_table[k] = \
			ft_strdup(msh->cmd_table[i].cmd[index]);
			k++;
			}
		}
		index++;
	}
}
