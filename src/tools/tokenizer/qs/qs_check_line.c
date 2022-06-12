/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_check_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:47:59 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/12 15:36:10 by oal-tena         ###   ########.fr       */
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

bool	redirect_postion(char *str, int postion_index)
{
	int		start_q;
	int		end_q;
	int		i;

	(void)postion_index;
	i = 0;
	start_q = 0;
	end_q = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE && start_q == 0)
			start_q = i;
		if (str[i] == SINGLE_QUOTE && start_q != 0)
			end_q = i;
		i++;
	}
	i = 0;
	while (str[i] == ' ')
		i++;
	if ((start_q > postion_index && end_q > postion_index) || \
	(start_q == 0 && end_q == 0 && postion_index != i))
		return (true);
	else
		return (false);
}

void	qs_check(t_qs **qs, char **str, int k, int len)
{
	int	i;
	int	index;

	i = 0;
	index = 1;
	while (str[k][i])
	{
		if (str[k][i] == SINGLE_QUOTE)
		{
			(*qs)->has_quote = true;
			(*qs)->quote_count++;
			while (str[k][i + index] && str[k][i + index] != SINGLE_QUOTE && \
			(*qs)->quote_count == 1)
			{
				if (str[k][i + index] != DOUBLE_QUOTE || \
				str[k][i + index] != ' ')
					index++;
			}
			(*qs)->btn_q_word_count = index - 1;
		}
		else if (str[k][i] == '$' && valid_dollar_sign(str[k], i))
			(*qs)->has_dollar = true;
		else if (str[k][i] == '>' || str[k][i] == '<')
			(*qs)->is_redirect = redirect_postion(str[k], i);
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

