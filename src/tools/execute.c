/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:08:02 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/25 08:08:02 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
TODO:this function need refocter and shift to ft_free or use ft_free_minishell
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
	execute command as child procces in order to keep minishell running
	TODO:	support characters like "|", ">", "<", etc.
			supoort cd,export,unset,env
*/
void	execute(char *path, char ***command_table)
{
	pid_t			pid;
	int				status;
	struct rusage	ru;
	char			*command;

	command = NULL;
	if (path[0] != '/')
	{
		command = ft_strjoin(command, "/bin/");
		command = ft_strjoin(command, path);
	}
	else
		command = ft_strdup(path);
	if (access(command, F_OK) == -1)
	{
		err_msg("command not found");
		free(command);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		execve(command, *command_table, NULL);
		perror("command failed");
		free_exit(&command, NULL, command_table);
		exit(1);
	}
	wait4(pid, &status, 0, &ru);
	free(command);
}
