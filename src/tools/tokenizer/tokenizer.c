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
		msh->command_table[i] = ft_split(tmp[i], ' ');
		check_command_table(msh, i);
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
