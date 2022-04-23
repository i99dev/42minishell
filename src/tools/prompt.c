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

void	free_exit(char **user_info, char **line, char ***command_table)
{
	free(*line);
	free(*user_info);
	if (*command_table)
		free(*command_table);
	exit(0);
}

/*
	signal handler to ignore crtl+c, must type "exit" to quit minishell
*/
void	signal_handler(int sig)
{
	(void)sig;
	info = get_user_inf();
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(info, 1);
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

	signal(SIGINT, signal_handler);
	user_info = get_user_inf();
	while (1)
	{
		line = readline(user_info);
		if (line == NULL)
			return ;
		if (ft_strncmp(line, "exit", 4) == 0)
			free_exit(&user_info, &line, &command_table);
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			rl_bind_key('\t', rl_complete);
			command_table = init_command_table(line);
			execute(command_table[0], command_table);
			free(line);
			line = NULL;
		}
		else
		{
			err_msg("empty command");
			free(line);
			line = NULL;
		}
	}
}
