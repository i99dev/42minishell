/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:21:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/07 08:33:45 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strtok(char *input, char delim)
{
	static char	*temp;
	char		*out;

	if (!input)
		input = temp;
	if (!input)
		return (NULL);
	while (*input)
	{
		if (*input == delim)
			input++;
		else
			break ;
	}
	if (!*input)
		return (NULL);
	out = input;
	while (*input)
	{
		if (*input == delim)
		{
			*input = '\0';
			temp = input + 1;
			return (out);
		}
		input++;
	}
	temp = input;
	return (out);
}

void	store_command_sequence(char *input, t_minishell *msh)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * 3);
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			temp[j] = input[i];
			j++;
		}
		i++;
	}
	temp[j] = 0;
	msh->command_seq = temp;
}

/*
	parses and splits input line into command table
	TODO:	support characters like "|", ">", "<", etc.
			handle double and single quotes
			fix tokenizer and return it.
			fix free msh->command_Table
*/



void	start_parser(t_minishell *msh)
{
	int	i;

	store_command_sequence(input, msh);
	i = 0;
	while (i < msh->token_count)
	{
		printf("|%s|\n", msh->token_ls[i].token);
		i++;
	}
	execute(msh);
}
