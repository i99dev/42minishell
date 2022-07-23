/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:25:29 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/23 10:13:14 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*get_io_filename(t_minishell *msh, int i, char *token, int index)
{
	msh->cmd_table[i]->is_filename = true;
	if (is_token(msh->cmd_table[i]->cmd[index]) && \
	ft_strlen(msh->cmd_table[i]->cmd[index]) <= 2 && \
	msh->cmd_table[i]->cmd[index + 1])
		return (ft_strdup(msh->cmd_table[i]->cmd[index + 1]));
	else
		return (check_file_name(msh->cmd_table[i]->cmd, token, index));
}

void	alloc_cmd(t_minishell *msh, int i)
{
	int	j;

	j = 0;
	msh->cmd_table[i]->exec_table = \
	(char **)malloc(sizeof(char *) * (msh->cmd_table[i]->arg_count + 1));
	msh->cmd_table[i]->tok = \
	(t_token **)malloc(sizeof(t_token *) * (msh->cmd_table[i]->token_count + 1));
	msh->cmd_table[i]->tok[msh->cmd_table[i]->token_count] = 0;
	msh->cmd_table[i]->filename = \
	(char **)malloc(sizeof(char *) * (msh->cmd_table[i]->token_count + 1));
	msh->cmd_table[i]->filename[msh->cmd_table[i]->token_count] = 0;
	while (j < msh->cmd_table[i]->token_count)
		msh->cmd_table[i]->tok[j++] = (t_token *)malloc(sizeof(t_token));
}

void	count_token(t_minishell *msh, int i)
{
	int		index;

	index = 0;
	msh->cmd_table[i]->token_count = 0;
	msh->cmd_table[i]->arg_count = 0;
	while (msh->cmd_table[i]->cmd[index])
	{
		if (is_token(msh->cmd_table[i]->cmd[index]) && \
			ft_strlen(msh->cmd_table[i]->cmd[index]) <= 2)
		{
			msh->cmd_table[i]->token_count++;
			if (msh->cmd_table[i]->cmd[index + 1] && \
				!is_token(msh->cmd_table[i]->cmd[index + 1]))
			{
				index += 2;
				continue ;
			}
		}
		else
			msh->cmd_table[i]->arg_count++;
		index++;
	}
	alloc_cmd(msh, i);
	msh->cmd_table[i]->exec_table[msh->cmd_table[i]->arg_count] = NULL;
}

void	_loop_n(t_minishell *msh, int i, t_counter *cnt)
{
	while (msh->cmd_table[i]->exec_table[cnt->s_i])
	{
		if (*msh->cmd_table[i]->exec_table[cnt->s_i] == 0)
			msh->cmd_table[i]->exec_table[cnt->s_i] = "\n";
		cnt->s_i++;
	}
}

bool	check_command_table(t_minishell *msh, int i)
{
	t_counter	*cnt;

	cnt = (t_counter *)malloc(sizeof(t_counter));
	cnt->s_i = 0;
	cnt->s_j = 0;
	cnt->s_k = 0;
	count_token(msh, i);
	while (msh->cmd_table[i]->cmd[cnt->s_i])
	{
		if (!_work_on_loop(msh, i, cnt))
			return (false);
		cnt->s_i++;
	}
	cnt->s_i = 0;
	_loop_n(msh, i, cnt);
	free(cnt);
	return (true);
}
