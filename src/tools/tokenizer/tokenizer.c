/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:12:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/24 06:23:35 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_tokenizer(char *str, t_minishell *msh)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = ft_split(str, ' ');
	msh->token_ls = (t_token *)malloc(sizeof(t_token));
	while (tokens[i])
	{
		if (tokens[i][0] == '\0')
			i++;
		else
		{
			msh->token_ls->token = ft_strdup(tokens[i]);
			i++;
		}
	}
}
