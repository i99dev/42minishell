/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:38:23 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/20 09:40:42 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_user_inf(void)
{
	char	*user;
	char	*host;
	char	*tmp;

	tmp = NULL;
	user = getenv("USER");
	host = getenv("HOSTNAME");
	tmp = ft_strjoin(tmp, BLUE"["GREEN);
	tmp = ft_strjoin(tmp, user);
	tmp = ft_strjoin(tmp, RED"@"GREEN);
	tmp = ft_strjoin(tmp, host);
	tmp = ft_strjoin(tmp, BLUE"]");
	tmp = ft_strjoin(tmp, ":");
	tmp = ft_strjoin(tmp, RED"> "RESET);
	return (tmp);
}

/*
@add history to the history commend line input 
@rl_bind_key ->when press tab get dir or complete the command
*/
void	prompt_commend(void)
{
	char	*line;


	while (1)
	{
		line = readline(get_user_inf());
		if (line == NULL)
			return ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			rl_bind_key('\t', rl_complete);
			free(line);
			line = NULL;
		}
		else
		{
			err_msg("empty command");
			free(line);
			line = NULL;
		}
	}
}
