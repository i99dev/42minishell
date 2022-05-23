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

/* get token value > "get this" */
void	get_io_filename(t_minishell *msh, int i, char *token, int index,int j)
{
	if (ft_strlen(msh->command_table[i][index]) == 1)
	{
		printf("redirect with space\n");
		msh->filename_ls[i][j]
			= ft_strdup(msh->command_table[i][index + 1]);
	}
	else
	msh->filename_ls[i][j]
			= ft_strdup(check_file_name(msh->command_table[i], token));
}

void	ft_check_command_table(t_minishell *msh, int i)
{
	int		index;
	int		wordindex;
	//char	temp[300];
/*count tokens*/
	//temp[0] = 0;
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

	/*allocate for token*/
	//temp[0] = 0;
	index = 0;
	int j=0;
	msh->token_ls[i] = (t_token **)malloc(sizeof(t_token*)*msh->token_count[i]);
	msh->filename_ls[i] = (char **)malloc(sizeof(char *) * msh->token_count[i]);
/*set_tokens
 go through every argument and check if token*/
	while (msh->command_table[i][index] && j< msh->token_count[i])
	{
		if (ft_strncmp(msh->command_table[i][index], ">>", 2) == 0)
			msh->token_ls[i][j]->token = ft_strdup(">>");
		else if (ft_strncmp(msh->command_table[i][index], "<<", 2) == 0)
			msh->token_ls[i][j]->token = ft_strdup("<<");
		else if (ft_strchr(msh->command_table[i][index], '<') != NULL)
		{
			msh->token_ls[i][j] = (t_token *)malloc(sizeof(t_token));
			msh->token_ls[i][j]->token = ft_strdup("<");
			get_io_filename(msh, i, "<", index,j);
			j++;
			if (j == 1)
			wordindex = index;
		}
		else if (ft_strchr(msh->command_table[i][index], '>') != NULL)
		{
			msh->token_ls[i][j] = (t_token *)malloc(sizeof(t_token));
			msh->token_ls[i][j]->token = ft_strdup(">");
			get_io_filename(msh, i, ">", index,j);
			j++;
			if (j == 1)
			wordindex = index;
		}
		/* else if */
		index++;
	}
	if (msh->token_count[i] > 0)
		msh->command_table[i][wordindex] = NULL;
	printf(" token count %d\n", msh->token_count[0]);
	/*
	if (msh->token_ls[i]->token == NULL)
	{
		free(msh->token_ls[i]);
		msh->token_ls[i] = NULL;
	}*/
}
/*
	make ***token
	token count is amount of found tokens
	each command arg has token
	type either -1, >, <,$, >>, <<

	command_type either bin or builtin
	if command is */

char *clean_str_space(char *str)
{
	int i;
	int j;
	char *new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] != ' ')
		{
			printf("char is:%c\n", str[i]);
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	init_command_table(t_minishell *msh)
{
	char	**tmp;
	int		table_count;
	int		i;
	//int		j;

	i = 0;
	tmp = ft_split(msh->line, '|');
	while (tmp && tmp[i] != NULL)
		i++;
	table_count = i;
	msh->command_table = (char ***)malloc(sizeof(char **) * table_count);
	msh->filename_ls = (char ***)malloc(sizeof(char **) * table_count);
	msh->token_ls = (t_token ***)malloc(sizeof(t_token **) * table_count);
	msh->token_count = (int *)malloc(sizeof(int));
	i = 0;
	msh->command_count = table_count;
	while (tmp && tmp[i])
	{
		// tmp[i] = clean_str_space(tmp[i]);
		msh->command_table[i] = ft_split(tmp[i], ' ');
		ft_check_command_table(msh, i);
		i++;
	}
	ft_check_quotes(msh);
	i = 0;
	while (tmp && tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	ft_tokenizer(t_minishell *msh)
{
	init_command_table(msh);
	define_type(msh);
}
