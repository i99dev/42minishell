/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_add_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:32:39 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/10 08:34:26 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	_expend_cmd(t_qs **qs, int len, char **str, int k)
{
	(void)str;
	(void)k;
	if (((*qs)->has_dollar && !(*qs)->has_qs_before && \
	!(*qs)->has_qs_after && (*qs)->has_quote && len > 1) || \
	((*qs)->has_dollar && !(*qs)->has_quote && \
	!(*qs)->has_qs_before &&!(*qs)->has_qs_after) || \
	(!(*qs)->has_dollar && !(*qs)->has_quote && \
	(*qs)->has_qs_before && (*qs)->has_qs_after) || \
	((*qs)->has_dollar && (*qs)->has_quote && !(*qs)->has_qs_before && \
	!(*qs)->has_qs_after && len == 1 && (*qs)->quote_count > 2))
		(*qs)->expand = true;
}

void	_remove_me(t_qs **qs, int len, char **str, int k)
{
	(void)str;
	(void)k;
	(void)len;
	if (((*qs)->has_quote && (*qs)->quote_count == 1 && \
	(*qs)->word_count == 0) || ((*qs)->has_quote && \
	(*qs)->quote_count == 2 && (*qs)->word_count == 0 && \
	((*qs)->has_qs_after || (*qs)->has_qs_after)))
		(*qs)->remove_me = true;
}

void	_clean_quote(t_qs **qs, int len, char **str, int k)
{
	if ((*qs)->has_quote && (*qs)->quote_count == 1 && (*qs)->word_count > 0)
	(*qs)->clean_quote = true;
	if (((*qs)->quote_count == 1 && (*qs)->word_count == 0) || \
	((*qs)->quote_count == 3 && (*qs)->word_count > 0) || \
	((*qs)->has_dollar && (*qs)->has_quote && ((*qs)->has_qs_after || \
	(*qs)->has_qs_before)) || ((*qs)->has_quote && !(*qs)->has_qs_after && \
	!(*qs)->has_qs_before && (*qs)->word_count > 0 && \
	(*qs)->quote_count == 2 && !(*qs)->expand) || \
	((*qs)->has_dollar && !(*qs)->has_qs_before && \
	!(*qs)->has_qs_after && (*qs)->has_quote && len == 1) || \
	((*qs)->has_quote && (*qs)->has_qs_after && (*qs)->quote_count == 2 && \
	(*qs)->word_count == 0) || \
	((*qs)->has_dollar && (*qs)->has_quote && !(*qs)->has_qs_before && \
	!(*qs)->has_qs_after && len == 1 && (*qs)->quote_count > 2) || \
	(!(*qs)->has_dollar && (*qs)->has_quote && (*qs)->quote_count > 2 && \
	(*qs)->word_count > 0 && qs_qstr_end(str[k])))
		(*qs)->clean_quote = true;
}

void	_add_qoute(t_qs **qs, int len, char **str, int k)
{
	(void)str;
	(void)k;
	(void)len;
	if (!(*qs)->has_quote && (*qs)->has_qs_before && (*qs)->has_qs_after)
	(*qs)->add_d_quote = true;
}

void	qs_add_rules(t_qs **qs, int len, char **str, int k)
{
	_expend_cmd(qs, len, str, k);
	_remove_me(qs, len, str, k);
	_clean_quote(qs, len, str, k);
	_add_qoute(qs, len, str, k);
	if ((*qs)->has_dollar && (*qs)->has_quote && len == 1 && \
	(*qs)->quote_count > 2)
		(*qs)->special_case = true;
}
