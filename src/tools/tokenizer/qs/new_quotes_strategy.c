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

#include "../../../../include/minishell.h"

char	*get_next_cmd(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isprint(line[i]))
		i++;
	if (line[i] == '\0')
		return (&line[i]);
	return (&line[i]);
}

char	*join_all_line(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		tmp = ft_strjoin(tmp, str[i]);
		i++;
	}
	return (tmp);
}

void	close_task(t_minishell *msh, t_qs **qs, char **d_quotes)
{
	int		i;
	int		start;
	char	*cmd;
	char	*tmp;

	i = 0;
	start = 0;
	d_quotes = ft_split(join_all_line(d_quotes), '|');
	tmp = ft_strdup("");
	while (d_quotes[i])
	{
		if (!(*qs)->remove_me && start == 0)
		{
			if (&d_quotes[ft_strlen(cmd + 1)] != NULL)
			{
				cmd = get_cmd_from_line(d_quotes[i]);
				msh->line = ft_strjoin(cmd, ft_strdup("\n"));
				msh->line = ft_strjoin(msh->line, ft_strdup(get_next_cmd(\
				&d_quotes[i][ft_strlen(msh->line)])));
			}
			start = 1;
		}
		else if (d_quotes[i] != NULL)
		{
			if (d_quotes[i][0] == '\0')
				msh->line = ft_strjoin(msh->line, ft_strdup(" "));
			else
				msh->line = ft_strjoin(msh->line, d_quotes[i]);
			if (d_quotes[i + 1] != NULL)
				msh->line = ft_strjoin(msh->line, ft_strdup("\n"));
		}
		if (d_quotes[i + 1])
			msh->line = ft_strjoin(msh->line, "|");
		i++;
		start = 0;
		add_space_redirect_char(msh->line);
		tmp = ft_strjoin(tmp, msh->line);
	}
	msh->line = ft_strdup(tmp);
}

void	qs_handle_space(t_qs **qs, char **str, int k, int len)
{
	(void)len;
	if ((!(*qs)->has_dollar && !(*qs)->has_qs_after && \
	!(*qs)->has_qs_before && !(*qs)->has_quote && \
	(!(*qs)->is_echo && (*qs)->btn_q_word_count > 0) && \
	!(*qs)->expand) || ((*qs)->special_case && (*qs)->quote_count == 4))
		str[k] = qs_remove_addtional_space(str[k]);
	if ((!(*qs)->has_quote && !(*qs)->is_echo && k == 0) || \
	(k > 0 && (*qs)->has_qs_before && (*qs)->has_qs_after  && !(*qs)->has_quote))
		str[k] = qs_remove_addtional_space(str[k]);
}

void	ft_quotes_strategy(t_minishell *msh)
{
	char	**d_quotes;
	t_qs	**qs;
	int		i;
	int		len;

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
		qs_handle_space(&qs[i], d_quotes, i, len);
		i++;
	}
	i = 0;
	while (d_quotes[i])
	{
		qs_handle(msh, &qs[i], d_quotes, i);
		i++;
	}
	free(msh->line);
	close_task(msh, qs, d_quotes);
}
