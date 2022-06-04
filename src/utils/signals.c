/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:09:46 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/04 17:50:27 by oal-tena         ###   ########.fr       */
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

void	define_exec_signals(t_minishell *msh)
{
	if (signal(SIGINT, interrupt_process))
		msh->exit_status = 130;
	if (signal(SIGQUIT, quit_process))
		msh->exit_status = 131;
}

void	define_input_signals(t_minishell *msh)
{
	if (signal(SIGINT, redisplay_prompt))
		msh->exit_status = 130;
	if (signal(SIGQUIT, SIG_IGN))
		msh->exit_status = 131;
}
