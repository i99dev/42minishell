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

#include "../../include/minishell.h"

char	*get_user_inf(void)
{
	char	*user;
	char	*host;
	char	*tmp;

	tmp = NULL;
	user = getenv("USER");
	if (!user)
		user = "root";
	host = getenv("HOSTNAME");
	if (!host)
		host = "localhost";
	tmp = ft_strjoin(tmp, BLUE"["GREEN);
	tmp = ft_strjoin(tmp, user);
	tmp = ft_strjoin(tmp, RED"@"GREEN);
	tmp = ft_strjoin(tmp, host);
	tmp = ft_strjoin(tmp, BLUE"]");
	tmp = ft_strjoin(tmp, ":");
	tmp = ft_strjoin(tmp, RED"> "RESET);
	return (tmp);
}

/*
	frees 2 strings and table and exits.
*/
void	free_exit(char **s1, char **s2, char ***table)
{
	int	i;

	if (*s1)
		free(*s1);
	if (*s2)
		free(*s2);
	if (*table)
	{
		i = 0;
		while ((*table)[i])
			free((*table)[i++]);
		free(*table);
	}
	exit(0);
}

/*
	signal handler to ignore crtl+c, must type "exit" or ctrl+D to quit minishell.
	TODO:	fix ctrl+C and ctrl+D should not print anything.
*/
void	signal_handler(int sig)
{
	char	*info;

	info = get_user_inf();
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(info, 1);
	}
	else if (sig == SIGINT)
	{
		rl_replace_line(info, 1);
	}
	free(info);
}

/*
@add history to the history commend line input 
@rl_bind_key ->when press tab get dir or complete the command
*/
void	prompt_commend(void)
{
	char	*line;
	char	**command_table;
	char	*user_info;

	command_table = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	/*
	ADD check for signal creation error
	if (signal(SIGINT, &sighandler) == SIG_ERR) {
        fprintf(stderr, "Could not set signal \n");
        return EXIT_FAILURE;
    }
	*/
	user_info = get_user_inf();
	while (1)
	{
		line = readline(user_info);
		if (line == NULL)
			free_exit(&user_info, &line, &command_table);
		if (ft_strlen(line) > 0 && ft_strncmp(line, "exit", 5) != 0)
		{
			add_history(line);
			rl_bind_key('\t', rl_complete);
			command_table = init_command_table(line);
			execute(command_table[0], &command_table);
		}
		else if (ft_strncmp(line, "exit", 5) == 0)
			free_exit(&user_info, &line, &command_table);
		else
		{
			err_msg("empty command");
		}
		free(line);
		line = NULL;
	}
}
