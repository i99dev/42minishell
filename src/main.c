/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:09:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/22 15:20:02 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_line(t_minishell *msh)
{
	msh->user_info = get_user_info(msh);
	msh->line = readline(msh->user_info);
	define_input_signals(msh);
	if (msh->line)
		add_history(msh->line);
	free(msh->user_info);
}

static void	minishill_start(t_minishell *msh, char **env)
{
	msh->env_table = init_table(env);
	msh->env = env2d(msh->env_table);
	while (1)
	{
		read_line(msh);
		ft_tokenizer(msh);
		start_parser(msh);
		init_execute(msh);
		if (msh->line)
			free(msh->line);
	}
}

void	init_minishell(t_minishell *minishell)
{
	minishell->cmd_table = NULL;
	minishell->line = NULL;
	minishell->user_info = NULL;
	minishell->exit_status = 0;
	minishell->quote_count = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	init_minishell(&minishell);
	minishill_start(&minishell, env);
	ft_free_minishell(&minishell);
	return (0);
}
