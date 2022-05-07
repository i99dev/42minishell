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

#include "../../../include/minishell.h"

void	execute(t_minishell *msh)
{
	pid_t			pid;
	int				status;
	struct rusage	ru;
	char			*command;

	if (msh->line[0] != '/')
	{
		command = NULL;
		command = ft_strjoin(command, "/bin/");
		command = ft_strjoin(command, msh->command_table[0][0]);
	}
	else
		command = ft_strdup(msh->line);
	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		execve(command, msh->command_table[0], __environ);
		perror("command failed");
		exit(1);
	}
	wait4(pid, &status, 0, &ru);
	free(command);
}
