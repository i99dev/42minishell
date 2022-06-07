/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quotes_strategy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 03:28:21 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/07 03:28:39 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	qs_add_rules(t_qs **qs)
{
	if ((((*qs)->has_dollar && (!(*qs)->has_qs_before && !(*qs)->has_qs_after))) || \
	((*qs)->has_dollar && (*qs)->has_quote))
		(*qs)->expand = true;
	if (((*qs)->has_quote && (*qs)->quote_count == 1 && (*qs)->word_count == 0) || \
	(!(*qs)->has_quote && (*qs)->quote_count == 0 && (*qs)->word_count == 0))
		(*qs)->remove_me = true;
	if ((*qs)->has_quote && (*qs)->quote_count == 1 && (*qs)->word_count > 0)
		(*qs)->clean_quote = true;
	if (!(*qs)->has_quote && (*qs)->has_qs_before && (*qs)->has_qs_after)
		(*qs)->add_d_quote = true;
	if (((*qs)->quote_count == 1 && (*qs)->word_count == 0) || \
	((*qs)->quote_count == 3 && (*qs)->word_count > 0))
		(*qs)->clean_quote = true;
}

void	qs_check(t_qs **qs, char **str, int k)
{
	int	i;

	i = 0;
	while (str[k][i])
	{
		if (str[k][i] == SINGLE_QUOTE)
		{
			(*qs)->has_quote = true;
			(*qs)->quote_count++;
		}
		else if (str[k][i] == '$' && valid_dollar_sign(str[k], i))
			(*qs)->has_dollar = true;
		if (k != 0 && str[k - 1][ft_strlen(str[k - 1]) - 1] == SINGLE_QUOTE)
			(*qs)->has_qs_before = true;
		if (str[k + 1] != NULL && str[k + 1][0] == SINGLE_QUOTE)
			(*qs)->has_qs_after = true;
		if (ft_isalnum(str[k][i]))
			(*qs)->word_count++;
		i++;
	}
	qs_add_rules(qs);
}

void	qs_handle(t_minishell *msh, t_qs **qs, char **str, int k)
{
	// printf("tmp is:%s\n", str[k]);
	if ((*qs)->expand)
		str[k] = expand_cmd(msh, str[k]);
	if ((*qs)->add_d_quote)
	{
		str[k] = qs_remove_single_quote(ft_strdup(str[k]));
		str[k] = ft_strjoin(ft_strdup("\""), ft_strdup(str[k]));
		str[k] = ft_strjoin(str[k], ft_strdup("\""));
		str[k] = qs_remove_space(str[k]);
	}
	if ((*qs)->clean_quote)
	{
		str[k] = qs_remove_single_quote(str[k]);
	}
	if ((*qs)->add_s_quote)
	{
		str[k] = qs_remove_single_quote(str[k]);
		str[k] = ft_strjoin(ft_strdup("'"), str[k]);
		str[k] = ft_strjoin(str[k], ft_strdup("'"));
		// str[k] = qs_remove_space(str[k]);
	}
	// printf("update is:%s\n", str[k]);
}

void	ft_quotes_strategy(t_minishell *msh)
{
	char	**d_quotes;
	t_qs	**qs;
	int		i;

	d_quotes = ft_split(msh->line, DOUBLE_QUOTE);
	i = 0;
	while (d_quotes[i])
		i++;
	qs = (t_qs **)malloc(sizeof(t_qs *) * i);
	i = 0;
	while (d_quotes[i])
	{
		qs_init(&qs[i]);
		qs_check(&qs[i], d_quotes, i);
		// qs_print(&qs[i], d_quotes[i]);
		i++;
	}
	i = 0;
	while (d_quotes[i])
	{
		qs_handle(msh, &qs[i], d_quotes, i);
		i++;
	}
	i = 0;
	while (d_quotes[i])
	{
		if (i == 0)
		{
			free(msh->line);
			msh->line = ft_strdup(d_quotes[i]);
		}
		else if (d_quotes[i] != NULL && !qs[i]->remove_me)
			msh->line = ft_strjoin(msh->line, d_quotes[i]);
		i++;
	}
}
