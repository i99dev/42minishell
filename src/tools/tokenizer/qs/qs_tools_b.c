/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_tools_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:56:03 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/12 08:17:12 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	qs_init(t_qs **qs)
{
	*qs = (t_qs *)malloc(sizeof(t_qs));
	(*qs)->has_quote = false;
	(*qs)->has_dollar = false;
	(*qs)->has_qs_before = false;
	(*qs)->has_qs_after = false;
	(*qs)->add_d_quote = false;
	(*qs)->is_echo = false;
	(*qs)->keep_space = false;
	(*qs)->expand = false;
	(*qs)->remove_me = false;
	(*qs)->clean_quote = false;
	(*qs)->add_s_quote = false;
	(*qs)->special_case = false;
	(*qs)->quote_count = 0;
	(*qs)->word_count = 0;
}

void	qs_print(t_qs **qs, char *str)
{
	printf("--------------------\n");
	printf("str is |%s|\n", str);
	printf("has_quote: %d\n", (*qs)->has_quote);
	printf("has_dollar: %d\n", (*qs)->has_dollar);
	printf("has_qs_before: %d\n", (*qs)->has_qs_before);
	printf("has_qs_after: %d\n", (*qs)->has_qs_after);
	printf("need expand: %d\n", (*qs)->expand);
	printf("special case: %d\n", (*qs)->special_case);
	printf("is_echo: %d\n", (*qs)->is_echo);
	printf("keep_space: %d\n", (*qs)->keep_space);
	printf("quote_count: %d\n", (*qs)->quote_count);
	printf("word_count: %d\n", (*qs)->word_count);
	printf("add_d_quote: %d\n", (*qs)->add_d_quote);
	printf("remove_me: %d\n", (*qs)->remove_me);
	printf("add_s_quote: %d\n", (*qs)->add_s_quote);
	printf("clean_quote: %d\n", (*qs)->clean_quote);
	printf("--------------------\n");
}

char	*qs_remove_single_quote(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] != SINGLE_QUOTE)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*qs_remove_space(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (ft_isprint(str[i]) && str[i] != ' ')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	tmp[i] = '\0';
	return (tmp);
}

bool	valid_dollar_sign(char *str, int i)
{
	if (str[i] == '$' && isalnum(str[i + 1]))
		return (true);
	return (false);
}
