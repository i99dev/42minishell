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
/* init filename */
void	get_io_filename(t_minishell *msh, int i, char *token)
{
	msh->filename_ls[i][msh->token_count[i]]=ft_strdup(check_file_name(msh->command_table[i],token));
	//msh->command_table[i][index]=NULL;

	printf("file: %s\n", msh->filename_ls[i][msh->token_count[i]]);
}
void	ft_check_command_table(t_minishell *msh, int i)
{
	int		index;
	int		wordindex;
	char	temp[300];

	temp[0]=0;
	index = 0;
	msh->token_ls[i] = (t_token *)malloc(sizeof(t_token));
	msh->token_ls[i]->token = NULL;
	msh->token_count[i]=0;
	msh->filename_ls[i] = (char **)malloc(sizeof(char *) * 2);

	while (msh->command_table[i][index])
	{
		if (ft_strncmp(msh->command_table[i][index], ">>", 2) == 0)
			msh->token_ls[i]->token = ft_strdup(">>");
		else if (ft_strncmp(msh->command_table[i][index], "<<", 2) == 0)
			msh->token_ls[i]->token = ft_strdup("<<");
		else if (ft_strchr(msh->command_table[i][index], '<') != NULL)
		{
			msh->token_ls[i]->token = strcat(temp,msh->command_table[i][index]);
			get_io_filename(msh,i,"<");
			msh->token_count[i]++;
			if(msh->token_count[i]==1)
			wordindex=index;
		}
		else if (ft_strchr(msh->command_table[i][index], '>') != NULL)
		{
			msh->token_ls[i]->token = strcat(temp,msh->command_table[i][index]);
			get_io_filename(msh,i,">");
			msh->token_count[i]++;
			if(msh->token_count[i]==1)
			wordindex=index;
		}
		msh->token_ls[i]->token=ft_strdup(temp);
		index++;
	}
	if (msh->token_count[i]>0)
	msh->command_table[i][wordindex]=NULL;
	printf(" token count %d\n",msh->token_count[0]);
	if (msh->token_ls[i]->token == NULL)
	{
		free(msh->token_ls[i]);
		msh->token_ls[i] = NULL;
	}
}

void	init_command_table(t_minishell *msh)
{
	char	**tmp;
	int		table_count;
	int		i;
	i = 0;
	tmp = ft_split(msh->line, '|');
	while (tmp && tmp[i] != NULL)
		i++;
	table_count = i;
	msh->command_table = (char ***)malloc(sizeof(char **) * table_count);
	msh->filename_ls = (char ***)malloc(sizeof(char **) * table_count);
	msh->token_ls = (t_token **)malloc(sizeof(t_token *) * table_count);
	msh->token_count = (int *)malloc(sizeof(int));
	i = 0;
	msh->command_count = table_count;
	while (tmp && tmp[i])
	{
		msh->command_table[i] = ft_split(tmp[i], ' ');
		ft_check_command_table(msh, i);
		i++;
	}
	printf("table number :%d\n", table_count);
	//msh->command_table[i] = NULL;
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
