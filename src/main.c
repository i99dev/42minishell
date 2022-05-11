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

//usr/bin/env clang++ $0 -o ${o=`mktemp`} && exec $o $*

#include "../include/minishell.h"

void	read_line(t_minishell *msh)
{
	msh->user_info = get_user_info();
	msh->line = readline(msh->user_info);
	if (msh->line)
		add_history(msh->line);
	free(msh->user_info);
}

static void	minishill_start(t_minishell *msh, char **env)
{
	msh->env_table = init_table(env);
	define_input_signals();
	while (1)
	{
		read_line(msh);
		if (ft_strncmp(msh->line, "exit", 4) == 0)
			ft_free_minishell(msh);
		ft_tokenizer(msh);
		start_parser(msh);
		init_execute(msh);
		if (msh->line)
			free(msh->line);
	}
}

void	init_minishell(t_minishell *minishell)
{
	minishell->command_table = NULL;
	minishell->line = NULL;
	minishell->user_info = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell);
	minishill_start(&minishell, env);
	ft_free_minishell(&minishell);
	return (0);
}
