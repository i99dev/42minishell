/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 05:25:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/05 05:26:04 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strinsert(char *str, char *in)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	temp = malloc(sizeof(char) * 200);
	i = 0;
	while (str[i] != '$')
	{
		temp[i] = str[i];
		i++;
	}
	k = i;
	j = 0;
	while (in[j])
	{
		temp[i] = in[j];
		j++;
		i++;
	}
	while (str[k] && str[k] != ' ' && str[k] != SINGLE_QUOTE)
		k++;
	while (str[k])
	{
		temp[i] = str[k];
		k++;
		i++;
	}
	temp[i] = 0;
	return (temp);
}