/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:26:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/22 07:29:48 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_dollar_quote(t_minishell *msh, int i, int j)
{
	char	*temp;

	temp = ft_strchr(msh->cmd_table[i]->cmd[j], '\"');
	if (temp)
	{
		if (temp[1] == '\"')
			return (true);
	}
	temp = ft_strchr(msh->cmd_table[i]->cmd[j], '\'');
	if (temp)
	{
		if (temp[1] == '\'')
			return (true);
	}
	return (false);
}

bool	special_char_with_dollar(char *word)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] && \
		(word[i + 1] == '+'))
			return (true);
		i++;
	}
	if (i == 1)
		return (true);
	return (false);
}
