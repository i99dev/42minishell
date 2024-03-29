/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 04:59:25 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/26 13:52:54 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	_handle_redirect_s_line(char *line, int *i, int *j, char *tmp)
{
	if (line[*i] && line[*i + 1])
	{
		if ((line[*i] == '<' && line[*i + 1] != '<') || \
		(line[*i] == '>' && line[*i + 1] != '>'))
		{
			tmp[(*j)++] = ' ';
			tmp[(*j)++] = line[(*i)++];
			tmp[(*j)++] = ' ';
		}
	}
}

void	_handle_redirect_d_line(char *line, int *i, int *j, char *tmp)
{
	if (line[*i] && line[*i + 1])
	{
		if ((line[*i] == '<' && line[*i + 1] == '<') || \
		(line[*i] == '>' && line[*i + 1] == '>'))
		{
			tmp[(*j)++] = ' ';
			tmp[(*j)++] = line[(*i)++];
			tmp[(*j)++] = line[(*i)++];
			tmp[(*j)++] = ' ';
		}
	}
}

void	add_space_redirect_char(t_minishell *msh)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(msh->line) * 2));
	while (msh->line[i])
	{
		_handle_redirect_s_line(msh->line, &i, &j, tmp);
		_handle_redirect_d_line(msh->line, &i, &j, tmp);
		tmp[j++] = msh->line[i++];
	}
	tmp[j] = '\0';
	free(msh->line);
	msh->line = NULL;
	msh->line = tmp;
}

bool	is_parameter(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '$');
	if (tmp)
	{
		if (tmp[1] && tmp[1] == ' ' && ft_strchr(&tmp[1], '$'))
			return (true);
		if ((tmp[1] && !is_case_alph(tmp[1]) && \
		tmp[1] != ' ') || ft_strlen(tmp) == 1)
			return (false);
	}
	else
		return (false);
	return (true);
}
