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
	if (msh->line)
		add_history(msh->line);
	free(msh->user_info);
}

bool	check_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (i == 0)
		{
			while (str[i] && str[i] == ' ' && \
			(str[i] != '\"' || str[i] != '\''))
				i++;
			if (str[i] && str[i] == '|')
				return (false);
		}
		if (str[i] && isalnum(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static void	minishill_start(t_minishell *msh, char **env)
{
	msh->env_table = init_table(env);
	while (1)
	{
		define_input_signals(msh);
		if (msh->line)
		{
			free(msh->line);
			ft_command_table_free(msh);
		}
		read_line(msh);
		if (!msh->line)
		{
			ft_free_hash(msh->env_table);
			exit(0);
		}
		if (!ft_strlen(msh->line) || !check_valid_line(msh->line))
		{
			free(msh->line);
			msh->line = NULL;
			continue ;
		}
		if (!ft_tokenizer(msh))
			continue ;
		init_execute(msh);
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
	init_minishell(&minishell);
	minishill_start(&minishell, env);
	ft_free_minishell(&minishell);
	return (0);
}
