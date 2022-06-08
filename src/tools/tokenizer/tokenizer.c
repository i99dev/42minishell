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
	msh->cmd_table = (t_cmdt *)malloc(sizeof(t_cmdt) * table_count);
	msh->command_count = table_count;
	return (tmp);
}

char	**split_first_word(char *str)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char **)malloc(sizeof(char *) * 2);
	tmp[0] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		tmp[0][j] = str[i];
		i++;
		j++;
	}
	tmp[0][j] = '\0';
	tmp[0] = ft_strdup(tmp[0]);
	while (str[i] == ' ')
		i++;
	if (str[i])
	{
		tmp[1] = ft_strdup(&str[i]);
		tmp[2] = NULL;
	}
	return (tmp);
}

void	init_command_table(t_minishell *msh)
{
	char	**tmp;
	int		i;

	i = 0;
	ft_quotes_strategy(msh);
	tmp = tk_split_pip(msh);
	while (tmp && tmp[i])
	{
		msh->cmd_table[i].cmd = split_first_word(tmp[i]);
		ft_handle_quotes(msh);
		ft_special_case(msh);
		check_command_table(msh, i);
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

void	ft_tokenizer(t_minishell *msh)
{
	init_command_table(msh);
	define_type(msh);
}
