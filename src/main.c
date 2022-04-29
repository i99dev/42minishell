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

t_hash_table	*init_table(char **env)
{
	t_hash_table		*table;
	int					len;

	len = 0;
	while (env[len])
		len++;
	table = create_hash_table(len * 2);
	len = 0;
	while (env[len])
	{
		insert_hash(table, env[len]);
		len++;
	}
	return (table);
}

/*
we can implement a function and attach env value to it by bas **env
exmaple: int main(int argc, char **argv, char **env)
or we can use a __environ to get env value
*/
void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env_table = init_table(env);
	minishell->env = env;
	minishell->command_table = NULL;
	minishell->line = NULL;
	minishell->user_info = NULL;
	minishell->token_ls = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, env);
	prompt_commend(&minishell);
	ft_free_minishell(&minishell);
	return (0);
}
