/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:21:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/25 13:09:14 by oal-tena         ###   ########.fr       */
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

/*
	parses and splits input line into command table
	TODO:	support characters like "|", ">", "<", etc.
			handle double and single quotes
			fix tokenizer and return it.
*/

