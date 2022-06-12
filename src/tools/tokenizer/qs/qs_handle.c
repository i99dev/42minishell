/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:42:07 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/10 08:43:28 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*qs_special_case(t_minishell *msh, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(str, '\'');
	while (tmp[i])
	{
		if (tmp[i][0] != '$')
			tmp[i] = expand_cmd(msh, tmp[i]);
		else
		{
			tmp[i] = ft_strjoin(ft_strdup("'"), tmp[i]);
			tmp[i] = ft_strjoin(tmp[i], ft_strdup("'"));
		}
		i++;
	}
	i = 0;
	free(str);
	str = ft_strdup("");
	while (tmp[i])
	{
		str = ft_strjoin(str, tmp[i]);
		i++;
	}
	return (str);
}

char	*qs_remove_addtional_space(char *str)
{
	char	*new_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_string = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			{
				if (str[i + 2] != ' ')
				{
					new_string[j++] = '\n';
					i++;
				}
			}
			i++;
		}
		else
			new_string[j++] = str[i++];
	}
	new_string[j] = '\0';
	free(str);
	return (new_string);
}

void	_expande_line(t_minishell *msh, t_qs **qs, char **str, int k)
{
	if ((*qs)->expand && !(*qs)->special_case)
		str[k] = expand_cmd(msh, str[k]);
}

void	_handle_qoute(t_minishell *msh, t_qs **qs, char **str, int k)
{
	(void)msh;
	if ((*qs)->add_d_quote)
	{
		str[k] = qs_remove_space(str[k]);
		str[k] = qs_remove_single_quote(ft_strdup(str[k]));
		str[k] = ft_strjoin(ft_strdup("\""), ft_strdup(str[k]));
		str[k] = ft_strjoin(str[k], ft_strdup("\""));
		str[k] = qs_remove_space(str[k]);
	}
	if ((k == 0 && (*qs)->has_quote) ||(k > 1 && (*qs)->has_quote && !(*qs)->btn_q_word_count &&  !(*qs)->has_qs_before ) || (*qs)->quote_count == 8 || ((*qs)->has_quote && (*qs)->quote_count == 1) || \
	(!(*qs)->has_quote && !(*qs)->has_qs_before && (*qs)->quote_count != 3))
		str[k] = qs_remove_single_quote(str[k]);
	if ((*qs)->add_s_quote)
	{
	}
}

void	qs_handle(t_minishell *msh, t_qs **qs, char **str, int k)
{
	_expande_line(msh, qs, str, k);
	_handle_qoute(msh, qs, str, k);
	if ((*qs)->special_case)
		str[k] = qs_special_case(msh, str[k]);
}
