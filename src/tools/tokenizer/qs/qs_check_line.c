/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_check_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:47:59 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/12 09:42:57 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	qs_handle_sp_case(t_qs **qs, char **str, int *k)
{
	int	i;

	i = 0;
	if (str[*k] && str[*k + 1] && str[*k + 2])
	{
		while (str[*k + 1] && str[*k + 1][i] == ' ')
			i++;
		if (ft_strchr(str[*k], SINGLE_QUOTE) && \
		(!ft_strchr(str[*k + 1], SINGLE_QUOTE) && !str[*k + 1][i]) && \
		ft_strchr(str[*k + 2], SINGLE_QUOTE))
		{
			str[*k] = ft_strjoin(str[*k], ft_strdup("\""));
			str[*k] = ft_strjoin(str[*k], " ");
			str[*k + 1] = ft_strjoin(str[*k + 1], ft_strdup("\""));
			str[*k + 2] = ft_strjoin(ft_strdup("\""), str[*k + 2]);
			(*qs)->remove_me = false;
		}
	}
}

void	is_echo_pipe(t_qs **qs, char **str, int k)
{
	char	*tmp;

	tmp = ft_strdup(str[k]);
	if (_match_string(get_cmd_from_line(tmp), "echo"))
		(*qs)->is_echo = true;
	if (k != 0)
	{
		if (!ft_strchr(tmp, 124) && qs[-1]->is_echo)
			(*qs)->is_echo = true;
		if (ft_strchr(tmp, 124) && qs[-1]->is_echo)
			(*qs)->keep_space = true;
	}
	free(tmp);
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
	is_echo_pipe(qs, str, k);
	qs_add_rules(qs, len, str, k);
	if (len > 6)
		qs_handle_sp_case(qs, str, &k);
}
