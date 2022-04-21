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
Prompt Display when minishell start and waiting for user input
*/

void	prompt_commend(void)
{
	char	*user;
	char	*host;
	char	*line;
	
	user = getenv("USER");
	host = getenv("HOSTNAME");
	ft_putstr_fd(GREEN"[", 1);
	ft_putstr_fd(MAGENTA, 1);
	ft_putstr_fd(user, 1);
	ft_putstr_fd(GREEN"@", 1);
	ft_putstr_fd(CYAN, 1);
	ft_putstr_fd(host, 1);
	ft_putstr_fd(GREEN"]", 1);
	ft_putstr_fd(GREEN"$~ "RESET, 1);
	while(1)
	{
		line = readline("");
		add_history(line);
		free(line);
	}
}
