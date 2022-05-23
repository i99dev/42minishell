/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:09:46 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/23 13:03:02 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	interrupt_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

static void	redisplay_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	quit_process(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	define_exec_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}

void	define_input_signals(void)
{
	signal(SIGINT, redisplay_prompt);
	signal(SIGQUIT, SIG_IGN);
}