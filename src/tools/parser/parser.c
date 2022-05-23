/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:21:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/23 13:20:39 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/*
void	ft_handel_token(t_minishell *msh, int index)
{
	msh->fd_std[index] = (int *)malloc(sizeof(int) * 2);
	printf("token: %s\n", msh->token_ls[index]->token);
	if (ft_strncmp(msh->token_ls[index]->token, "<", ft_strlen("<")) == 0)
		ft_redirect_in(msh, index);
	if (ft_strncmp(msh->token_ls[index]->token, ">", ft_strlen(">")) == 0)
		ft_redirect_out(msh, index);
	if (ft_strncmp(msh->token_ls[index]->token, ">>", ft_strlen(">>")) == 0)
		ft_redirect_out(msh, index);
	if (ft_strncmp(msh->token_ls[index]->token, "<<", ft_strlen("<<")) == 0)
		here_doc(msh, index);
}
*/
void	start_parser(t_minishell *msh)
{
	int	i;

	msh->fd_std = (int **)malloc(sizeof(int *) * msh->command_count + 1);
	i = 0;
	while (i < msh->command_count)
	{
		if (msh->token_ls[i] != NULL)
		{
			//ft_handel_token(msh, i);
		}
		printf("\n");
		i++;
	}
}
