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

char	*ft_without_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 - 2));
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else
			new[j++] = str[i++];
	}
	return (new);
}

void	ft_handle_double_quotes(t_minishell *msh, char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	tmp = ft_without_quotes(tmp);
	free(*str);
	printf("tmp: %s\n", &tmp[1]);
	tmp = find_hash(msh->env_table, &tmp[1]);
	if (tmp)
		*str = ft_strdup(tmp);
	else
		*str = ft_strdup("");
	free(tmp);
}

void	ft_check_quotes(t_minishell *msh)
{
	int	i;
	int	j;
	int	k;
	int	count;

	i = 0;
	count = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->command_table[i][j])
		{
			k = 0;
			while (msh->command_table[i][j][k])
			{
				if (msh->command_table[i][j][k] == DOUBLE_QUOTE)
					count++;
				if (count == 2)
					ft_handle_double_quotes(msh, &msh->command_table[i][j]);
				k++;
			}
			j++;
		}
		i++;
	}
}
