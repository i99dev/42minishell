/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 03:42:11 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/05 03:44:39 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	q_count_quotes(t_minishell *msh)
{
	int		i;
	int		first_quote;
	int		q_count;

	i = 0;
	q_count = 0;
	first_quote = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == DOUBLE_QUOTE && first_quote == 0)
			first_quote = DOUBLE_QUOTE;
		else if (msh->line[i] == SINGLE_QUOTE && first_quote == 0)
			first_quote = SINGLE_QUOTE;
		i++;
		if (msh->line[i] && msh->line[i] == first_quote)
		{
			q_count++;
			first_quote = 0;
			i++;
		}
	}
	return (q_count);
}

int	q_start_remove_quotes(t_minishell *msh, char *tmp, int *start)
{
	int	i;

	i = 0;
	while (i <= *start)
	{
		tmp[i] = msh->line[i];
		i++;
	}
	*start = i;
	return (i + 1);
}

int	q_remove_quotes(t_minishell *msh, int start, int end, int q_index)
{
	char	*temp;
	int		j;
	int		k;
	int		ret;

	msh->quotes[q_index] = malloc(sizeof(char) * (end - start - 1) + 1);
	temp = malloc(sizeof(char) * (ft_strlen(msh->line) - (end - start) + 2));
	ret = q_start_remove_quotes(msh, temp, &start);
	j = start;
	k = 0;
	while (start < end)
	{
		msh->quotes[q_index][k] = msh->line[start];
		start++;
		k++;
	}
	msh->quotes[q_index][k] = 0;
	while (msh->line[end])
	{
		temp[j] = msh->line[end];
		end++;
		j++;
	}
	temp[j] = 0;
	free(msh->line);
	msh->line = temp;
	return (ret);
}
