/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:21:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/11 09:14:47 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_handel_token(t_minishell *msh, int i)
{
	if (ft_strncmp(msh->token_ls[i]->token, "<", ft_strlen("<")) == 0)
		return ;
	if (ft_strncmp(msh->token_ls[i]->token, ">", ft_strlen(">")) == 0)
		return ;
	if (ft_strncmp(msh->token_ls[i]->token, ">>", ft_strlen(">>")) == 0)
		return ;
	if (ft_strncmp(msh->token_ls[i]->token, "<<", ft_strlen("<<")) == 0)
		return ;
}

void	start_parser(t_minishell *msh)
{
	int	i;
	int	j;

	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->command_table[i][j])
		{
			/*
			printf("%s ", msh->command_table[i][j]);
			*/
			j++;
		}
		if (msh->token_ls[i] != NULL)
		{
			// line under me, only for dubg purposes
			printf("commmend number %d ", i);
			printf("toke type is :%s\n", msh->token_ls[i]->token);
			ft_handel_token(msh, i);
		}
		printf("\n");
		i++;
	}
}
