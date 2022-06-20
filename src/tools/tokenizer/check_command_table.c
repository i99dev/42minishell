/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:25:29 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/20 13:35:42 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


char	*get_io_filename(t_minishell *msh, int i, char *token, int index)
{
	if (is_token(msh->cmd_table[i]->cmd[index]) && \
	ft_strlen(msh->cmd_table[i]->cmd[index]) <= 2 && msh->cmd_table[i]->cmd[index + 1])
	{
		//printf("redirect with space\n");
		return (ft_strdup(msh->cmd_table[i]->cmd[index + 1]));
	}
	else
		return (check_file_name(msh->cmd_table[i]->cmd, token, index));
}

void	alloc_cmd(t_minishell *msh, int i, char ***exec, t_token **tok, char ***filename)
{
	int j;

	j = 0;
	*exec = (char **)malloc(sizeof(char *) * (msh->cmd_table[i]->arg_count + 1));
	tok = (t_token **)malloc(sizeof(t_token *) * msh->cmd_table[i]->token_count);
	*filename = (char **)malloc(sizeof(char *) * msh->cmd_table[i]->token_count);
	while (j < msh->cmd_table[i]->token_count)
		tok[j++] = (t_token *)malloc(sizeof(t_token));
}

bool	is_token(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (true);
	else if (str[0] == '>')
		return (true);
	else if (str[0] == '<')
		return (true);
	return (false);
}

char *clean_all_space(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(str));
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
	//printf("token count:%d\narg count:%d",msh->cmd_table[i]->token_count,msh->cmd_table[i]->arg_count);
	alloc_cmd(msh,i,&msh->cmd_table[i]->exec_table, msh->cmd_table[i]->tok, &msh->cmd_table[i]->filename);
	msh->cmd_table[i]->exec_table[msh->cmd_table[i]->arg_count] = NULL;
}

static int	tk_handle_redirect_in(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
	msh->cmd_table[i]->tok[*j] = (t_token *)malloc(sizeof(t_token));
	msh->cmd_table[i]->tok[*j]->token = ft_strdup("<");
	msh->cmd_table[i]->filename[*j] = \
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
	msh->cmd_table[i]->tok[*j] = (t_token *)malloc(sizeof(t_token));
	msh->cmd_table[i]->tok[*j]->token = ft_strdup(">");
	msh->cmd_table[i]->filename[*j] = \
	get_io_filename(msh, i, ">", index);
	(*j)++;
	if (*j == 1)
		wordindex = index;
	return (wordindex);
}

bool	check_command_table(t_minishell *msh, int i)
{
	int		index;
	int		j;
	int		k;

	index = 0;
	j = 0;
	k = 0;
	count_token(msh, i);
	msh->cmd_table[i]->tok = (t_token **)malloc(sizeof(t_token *) * msh->cmd_table[i]->token_count);
	while (msh->cmd_table[i]->cmd[index])
	{
		if (!ft_strncmp(msh->cmd_table[i]->cmd[index], "$?", 2))
		{
			msh->cmd_table[i]->cmd[index] = expand_cmd(msh,msh->cmd_table[i]->cmd[index]);
		}
		if (ft_strlen(msh->cmd_table[i]->cmd[index])==2 && ft_strncmp(msh->cmd_table[i]->cmd[index], ">>", 2) == 0)
		{
			if (!msh->cmd_table[i]->cmd[index+1])
				return false;
			msh->cmd_table[i]->tok[j] = (t_token *)malloc(sizeof(t_token));
			msh->cmd_table[i]->tok[j]->token = ft_strdup(">>");
			msh->cmd_table[i]->filename[j] = \
				get_io_filename(msh, i, ">>", index);
			j++;
		}
		else if (ft_strlen(msh->cmd_table[i]->cmd[index])==2  && ft_strncmp(msh->cmd_table[i]->cmd[index], "<<", 2) == 0)
		{
			if (!msh->cmd_table[i]->cmd[index+1])
				return false;
			msh->cmd_table[i]->tok[j] = (t_token *)malloc(sizeof(t_token));
			msh->cmd_table[i]->tok[j]->token = ft_strdup("<<");
			msh->cmd_table[i]->filename[j] = \
			get_io_filename(msh, i, "<<", index);
			j++;
		}
		else if (ft_strlen(msh->cmd_table[i]->cmd[index])==1  && msh->cmd_table[i]->cmd[index][0] == '<')
		{
			if (!msh->cmd_table[i]->cmd[index+1])
				return false;
			tk_handle_redirect_in(msh, i, &j, index);
		}
		else if (ft_strlen(msh->cmd_table[i]->cmd[index])==1  && msh->cmd_table[i]->cmd[index][0] =='>')
		{
			if (!msh->cmd_table[i]->cmd[index+1])
				return false;
			tk_handle_redirect_out(msh, i, &j, index);
		}
		else if ((j == 0) || (ft_strncmp(msh->cmd_table[i]->cmd[index], \
			msh->cmd_table[i]->filename[j - 1], \
			ft_strlen(msh->cmd_table[i]->cmd[index]))))
		{
			if(msh->cmd_table[i]->cmd[index])
			{
				if(msh->cmd_table[i]->cmd[index][0] == '\r')
				msh->cmd_table[i]->cmd[index]=ft_strtrim(msh->cmd_table[i]->cmd[index],"\r");
				msh->cmd_table[i]->exec_table[k] = \
				ft_strdup(msh->cmd_table[i]->cmd[index]);
				k++;
			}
		}
		index++;
	}
	index=0;
	while (msh->cmd_table[i]->exec_table[index])
	{
		if(*msh->cmd_table[i]->exec_table[index] == 0)
			msh->cmd_table[i]->exec_table[index] = "\n";
		index++;
	}
	return true;
}
