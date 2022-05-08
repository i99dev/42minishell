/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:09:46 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/08 11:17:39 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler(int sig)
{
	char	*info;

	info = get_user_info();
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(info, 1);
	}
	else if (sig == SIGINT)
	{
		rl_replace_line(info, 1); /* this one not work on 42 lab*/
	}
	free(info);
}

void	define_input_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
