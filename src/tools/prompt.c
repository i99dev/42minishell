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

/*
@add history to the history commend line input 
@rl_bind_key ->when press tab get dir or complete the command
*/
void	prompt_commend(void)
{
	char	*line;

	while (1)
	{
		line = readline("$> ");
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
