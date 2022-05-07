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

#include "../include/minishell.h"

/*
	signal handler to ignore crtl+c, must type "exit" or ctrl+D to quit minishell.
	TODO:	fix ctrl+C and ctrl+D should not print anything.
*/
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
		// rl_replace_line(info, 1); /* this one not work on 42 lab*/
	}
	free(info);
}

/*
@add history to the history commend line input 
@rl_bind_key ->when press tab get dir or complete the command
*/
void	prompt_commend(t_minishell *msh)
{
	(void)msh;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
