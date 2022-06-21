/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 05:25:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/22 05:27:56 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_quotes(t_minishell *msh)
{
	msh->quote_count = q_count_quotes(msh);
	if (msh->quote_count)
		msh->quotes = malloc(sizeof(char *) * msh->quote_count);
}

void	ft_check_quotes(t_minishell *msh)
{
	int	i;
	int	start;
	int	first_quote;
	int	j;

	init_quotes(msh);
	i = 0;
	j = 0;
	first_quote = 0;
	while (msh->line[i])
	{
		if ((msh->line[i] == DOUBLE_QUOTE || \
		msh->line[i] == SINGLE_QUOTE) && first_quote == 0)
		{
			first_quote = msh->line[i];
			start = i;
		}
		i++;
		if (msh->line[i] && msh->line[i] == first_quote)
		{
			i = q_remove_quotes(msh, start, i, j);
			j++;
			first_quote = 0;
		}
	}
}
