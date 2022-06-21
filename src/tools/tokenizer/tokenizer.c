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

char	*clean_str_space(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] != ' ')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**tk_split_pip(t_minishell *msh)
{
	char	**tmp;
	int		table_count;
	int		i;

	i = 0;
	tmp = ft_split(msh->line, '|');
	while (tmp && tmp[i] != NULL)
		i++;
	table_count = i;
	msh->cmd_table = (t_cmdt **)malloc(sizeof(t_cmdt *) * table_count);
	msh->command_count = table_count;
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

void	_handle_redirect_s_line(char *line, int *i, int *j, char *tmp)
{
	if (line[*i] && line[*i + 1])
	{
		if ((line[*i] == '<' && line[*i + 1] != '<') || \
		(line[*i] == '>' && line[*i + 1] != '>'))
		{
			tmp[(*j)++] = ' ';
			tmp[(*j)++] = line[(*i)++];
			tmp[(*j)++] = ' ';
		}
	}
}

void	_handle_redirect_d_line(char *line, int *i, int *j, char *tmp)
{
	if (line[*i] && line[*i + 1])
	{
		if ((line[*i] == '<' && line[*i + 1] == '<') || \
		(line[*i] == '>' && line[*i + 1] == '>'))
		{
			tmp[(*j)++] = ' ';
			tmp[(*j)++] = line[(*i)++];
			tmp[(*j)++] = line[(*i)++];
			tmp[(*j)++] = ' ';
		}
	}
}

void	add_space_redirect_char(t_minishell *msh)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(msh->line) * 2));
	while (msh->line[i])
	{
		_handle_redirect_s_line(msh->line, &i, &j, tmp);
		_handle_redirect_d_line(msh->line, &i, &j, tmp);
		tmp[j++] = msh->line[i++];
	}
	tmp[j] = '\0';
	tmp = ft_strdup(tmp);
	free(msh->line);
	msh->line = tmp;
}

void	init_command_table(t_minishell *msh)
{
	char	**tmp;
	int		i;

	i = 0;
	ft_check_quotes(msh);
	add_space_redirect_char(msh);
	tmp = tk_split_pip(msh);
	while (tmp && tmp[i])
	{
		msh->cmd_table[i] = (t_cmdt *)malloc(sizeof(t_cmdt));
		msh->cmd_table[i]->cmd = ft_split(tmp[i], ' ');
		msh->cmd_table[i]->cmd_count = count_cmds(msh->cmd_table[i]->cmd);
		i++;
	}
	i = 0;
	while (tmp && tmp[i])
	{
		free(tmp[i]);
		i++;
	}
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
