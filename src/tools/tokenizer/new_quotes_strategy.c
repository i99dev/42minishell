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

char	*qs_remove_addtional_space(char *str)
{
	char	**tmp;
	int		i;

	tmp = ft_split(str, ' ');
	str = ft_strdup("");
	i = 0;
	while (tmp[i])
	{
		if (i != 0)
			str = ft_strjoin(str, ft_strdup(" "));
		str = ft_strjoin(str, tmp[i]);
		i++;
	}
	str = ft_strdup(str);
	free(tmp);
	return (str);
}

void	qs_add_rules(t_qs **qs, int len)
{
	if (((*qs)->has_dollar && !(*qs)->has_qs_before && !(*qs)->has_qs_after && (*qs)->has_quote && len > 1) || \
	((*qs)->has_dollar && !(*qs)->has_quote && !(*qs)->has_qs_before &&!(*qs)->has_qs_after) || \
	(!(*qs)->has_dollar && !(*qs)->has_quote && (*qs)->has_qs_before && (*qs)->has_qs_after))
		(*qs)->expand = true;
	if (((*qs)->has_quote && (*qs)->quote_count == 1 && (*qs)->word_count == 0))
		(*qs)->remove_me = true;
	if ((*qs)->has_quote && (*qs)->quote_count == 1 && (*qs)->word_count > 0)
		(*qs)->clean_quote = true;
	if (!(*qs)->has_quote && (*qs)->has_qs_before && (*qs)->has_qs_after)
		(*qs)->add_d_quote = true;
	if (((*qs)->quote_count == 1 && (*qs)->word_count == 0) || \
	((*qs)->quote_count == 3 && (*qs)->word_count > 0) || \
	((*qs)->has_dollar && (*qs)->has_quote && ((*qs)->has_qs_after || (*qs)->has_qs_before)) || \
	((*qs)->has_quote && !(*qs)->has_qs_after && !(*qs)->has_qs_before && (*qs)->word_count > 0 && (*qs)->quote_count > 2) || \
	((*qs)->has_dollar && !(*qs)->has_qs_before && !(*qs)->has_qs_after && (*qs)->has_quote && len == 1))
		(*qs)->clean_quote = true;
}

void	qs_check(t_qs **qs, char **str, int k, int len)
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
	qs_add_rules(qs, len);
}

void	qs_handle(t_minishell *msh, t_qs **qs, char **str, int k)
{
	if ((*qs)->expand)
		str[k] = expand_cmd(msh, str[k]);
	if ((*qs)->add_d_quote)
	{
		str[k] = qs_remove_space(str[k]);
		str[k] = qs_remove_single_quote(ft_strdup(str[k]));
		str[k] = ft_strjoin(ft_strdup("\""), ft_strdup(str[k]));
		str[k] = ft_strjoin(str[k], ft_strdup("\""));
		str[k] = qs_remove_space(str[k]);
	}
	if ((*qs)->clean_quote)
		str[k] = qs_remove_single_quote(str[k]);
	if ((*qs)->add_s_quote)
	{
		str[k] = qs_remove_single_quote(str[k]);
		str[k] = ft_strjoin(ft_strdup("'"), str[k]);
		str[k] = ft_strjoin(str[k], ft_strdup("'"));
		str[k] = qs_remove_space(str[k]);
	}
	if (!(*qs)->has_dollar && !(*qs)->has_qs_after && !(*qs)->has_qs_before && \
	!(*qs)->has_quote && !(*qs)->expand)
		str[k] = qs_remove_addtional_space(str[k]);
}


char	*get_cmd(char *line)
{
	char	*cmd;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	cmd = ft_substr(line, 0, i);
	return (cmd);
}


void	ft_quotes_strategy(t_minishell *msh)
{
	char	**d_quotes;
	t_qs	**qs;
	int		i;
	int  	len;

	d_quotes = ft_split(msh->line, DOUBLE_QUOTE);
	i = 0;
	while (d_quotes[i])
		i++;
	len = i;
	qs = (t_qs **)malloc(sizeof(t_qs *) * len);
	i = 0;
	while (d_quotes[i])
	{
		qs_init(&qs[i]);
		qs_check(&qs[i], d_quotes, i, len);
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
		if (i == 0 && !qs[i]->remove_me)
		{
			free(msh->line);
			msh->line = ft_strdup(get_cmd(d_quotes[i]));
			if (&d_quotes[ft_strlen(get_cmd(d_quotes[i]) + 1)] != NULL)
			{
				msh->line = ft_strjoin(msh->line, ft_strdup("\n"));
				msh->line = ft_strjoin(msh->line, ft_strdup(&d_quotes[i][ft_strlen(get_cmd(d_quotes[i])) + 1]));
			}
		}
		else if (d_quotes[i] != NULL && !qs[i]->remove_me)
		{
			if (d_quotes[i][0] == '\0')
				msh->line = ft_strjoin(msh->line, ft_strdup(" "));
			else
				msh->line = ft_strjoin(msh->line, d_quotes[i]);
			if (d_quotes[i + 1] != NULL)
				msh->line = ft_strjoin(msh->line, ft_strdup("\n"));
		}
		i++;
	}
}
