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

char	**tk_split_pip(t_minishell *msh)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(msh->line, '|');
	while (tmp && tmp[i] != NULL)
		i++;
	msh->command_count = i;
	return (tmp);
}

int	count_cmds(char **cmdtable)
{
	int	i;

	i = 0;
	while (cmdtable[i])
	{
		i++;
	}
	return (i);
}

bool  line_check_quotes(t_minishell *msh)
{
	int	i;

	i = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == '\'')
		{
			if (msh->line[i + 1] == '\'')
				i++;
			else
				return (false);
		}
		else if (msh->line[i] == '\"')
		{
			if (msh->line[i + 1] == '\"')
				i++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}


void	init_command_table(t_minishell *msh)
{
	char	**tmp;
	int		count_pipe;
	int		i;

	i = 0;
	ft_check_quotes(msh); // ;eak in this function 🙄
	add_space_redirect_char(msh);
	tmp = tk_split_pip(msh);
	count_pipe = 0;
	while (tmp[count_pipe])
		count_pipe++;
	msh->cmd_table = (t_cmdt **)malloc(sizeof(t_cmdt *) * count_pipe);
	while (tmp && tmp[i])
	{
		msh->cmd_table[i] = (t_cmdt *)malloc(sizeof(t_cmdt));
		msh->cmd_table[i]->cmd = ft_split(tmp[i], ' ');
		msh->cmd_table[i]->cmd_count = count_cmds(msh->cmd_table[i]->cmd);
		i++;
	}
	i = 0;
	while (tmp && tmp[i])
		free(tmp[i++]);
	free(tmp);
}

bool	ft_tokenizer(t_minishell *msh)
{
	int	i;

	init_command_table(msh);
	ft_special_case(msh);
	ft_handle_quotes(msh);
	i = 0;
	while (i < msh->command_count)
	{
		if (!check_command_table(msh, i))
			return (false);
		if (!msh->cmd_table[i]->arg_count)
		{
			if (msh->cmd_table[i]->token_count)
			{
				ft_redirect(msh, i);
				return (false);
			}
		}
		i++;
	}
	define_type(msh);
	return (true);
}
