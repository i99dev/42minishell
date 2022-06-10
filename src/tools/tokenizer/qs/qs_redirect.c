/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:01:28 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/10 09:58:42 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	_handle_redirect_s_line(char *line, int *i, int *j, char *tmp)
{
	if ((line[*i] == '<' && line[*i + 1] != '<') || \
	(line[*i] == '>' && line[*i + 1] != '>'))
	{
		tmp[(*j)++] = '\n';
		tmp[(*j)++] = line[(*i)++];
		tmp[(*j)++] = '\n';
	}
}

void	_handle_redirect_d_line(char *line, int *i, int *j, char *tmp)
{
	if ((line[*i] == '<' && line[*i + 1] == '<') || \
	(line[*i] == '>' && line[*i + 1] == '>'))
	{
		tmp[(*j)++] = '\n';
		tmp[(*j)++] = line[(*i)++];
		tmp[(*j)++] = line[(*i)++];
		tmp[(*j)++] = '\n';
	}
}

void	add_space_redirect_char(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 20));
	while (line[i])
	{
		_handle_redirect_s_line(line, &i, &j, tmp);
		_handle_redirect_d_line(line, &i, &j, tmp);
		tmp[j++] = line[i++];
	}
	tmp[j] = '\0';
	free(line);
	line = ft_strdup(tmp);
}
