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

t_hash_table	env_to_table(char **env)
{
	t_hash_table		table;
	int					len;

	len = 0;
	while (env[len])
		len++;
	table = create_hash_table(len);
	return (table);
}

/*
we can implement a function and attach env value to it by bas **env
exmaple: int main(int argc, char **argv, char **env)
or we can use a __environ to get env value
*/
void	init_minishell(t_minishell *minishell)
{
	(void)minishell;
	// minishell->env = env_map(__environ);
}

int	main(int argc, char **argv)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell);
	prompt_commend();
	return (0);
}
