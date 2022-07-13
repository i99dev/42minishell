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

bool	check_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			while (str[i] == ' ' && (str[i] != '\"' || str[i] != '\"'))
				i++;
			if (str[i] == '|')
			{
				return (false);
			}
		}
		if (isalnum(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static void	minishill_start(t_minishell *msh, char **env)
{
	msh->env_table = init_table(env);
	//print_hash(msh->env_table);
	//printf("%s",msh->env[0]);
	while (1)
	{
		read_line(msh);
		if (ft_strlen(msh->line) == 0)
		{
			free(msh->line);
			continue ;
		}
		if (!check_valid_line(msh->line))
			continue ;
		if (!ft_tokenizer(msh))
			continue ;
		init_execute(msh);
		if (msh->line)
		{
			free(msh->line);
			ft_command_table_free(msh);
		}
	}
}

void	init_minishell(t_minishell *minishell)
{
	minishell->cmd_table = NULL;
	minishell->line = NULL;
	minishell->user_info = NULL;
	minishell->exit_status = 0;
	minishell->quote_count = 0;
	minishell->quotes = NULL;
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
