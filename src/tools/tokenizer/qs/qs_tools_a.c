/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_tools_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:51:00 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/10 08:52:12 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

bool	qs_qstr_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{	
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '\0')
				return (true);
		}
		i++;
	}
	return (false);
}

char	*get_cmd_from_line(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[j] && line[j] == ' ')
		j++;
	while (line[j + i] && line[j + i] != ' ')
	{
		tmp[i] = line[j + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

bool	_match_string(char *str, char *match)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != match[j])
			return (false);
		i++;
		j++;
	}
	return (true);
}
