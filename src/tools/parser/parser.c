/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:21:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/30 17:25:45 by Dokcer           ###   ########.fr       */
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
void	init_command_table(char *input, t_minishell *msh)
{
	char	**command_table;
	int		i;
	int		j;
	char	***ctable;

	store_command_sequence(input, msh);
	i = 0;
	j = 0;
	printf("\nexecution table\n");
	printf("--------------\n");
	command_table = ft_split(input, '|');
	while (command_table[i])
	{
		printf("|%s|\n", command_table[i]);
		i++;
	}
	ctable = malloc(sizeof(char **) * i);
	while (j < i)
	{
		ctable[j] = ft_split(command_table[j], ' ');
		j++;
	}
	ctable[j] = 0;
	printf("\ncommand table\n");
	printf("--------------\n");
	printf("command_seq : '%s'\n", msh->command_seq);
	printf("--------------\n");
	i = 0;
	while (ctable[i] != 0)
	{
		j = 0;
		printf("execution %d :\n", i);
		while (ctable[i][j] != 0)
		{
			printf("command_table[%d][%d] : %s\n", i, j, ctable[i][j]);
			j++;
		}
		i++;
	}
	printf("\n");
	msh->command_table = ctable;
}