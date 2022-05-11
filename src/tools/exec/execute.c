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

void	add_bin_path(t_minishell *msh, int i)
{
	char	*command;

	if (msh->command_table[i][0][0] != '/')
	{
		command = NULL;
		command = ft_strjoin(command, "/bin/");
		command = ft_strjoin(command, msh->command_table[i][0]);
	}
	else
		command = ft_strdup(msh->command_table[i][0]);
	free(msh->command_table[i][0]);
	msh->command_table[i][0] = command;
}

/*
TODO: add support for builtin commands
*/
int	check_command_type(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < msh->command_count)
	{
		if (ft_strncmp(msh->command_table[i][0], "cd", 2) == 0)
		{
			exec_cd(msh, i);
			return (0);
		}
		if (ft_strncmp(msh->command_table[i][0], "pwd", 3) == 0)
		{
			exec_pwd();
			return (0);
		}
		else
			add_bin_path(msh, i);
		i++;
	}
	return (1);
}

/* 
	TODO: check whether command is bin or builtin command
		  check if is pipe or redirect or single command.
*/
void	init_execute(t_minishell *msh)
{
	if (!check_command_type(msh))
		return ;
	if (msh->command_count == 1)
		execute(msh, 0);
	else if (msh->command_count == 2)
		execute_pipe(msh, 0);
	else if (msh->command_count > 2)
		pipe_recursive(msh, 0, STDIN_FILENO);
}

void	execute(t_minishell *msh, int i)
{
	pid_t			pid;
	int				status;
	struct rusage	ru;

	printf("command is :%s\n", msh->command_table[0][0]);
	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		execve(msh->command_table[i][0], msh->command_table[i], __environ);
		perror("command failed");
	}
	wait4(pid, &status, 0, &ru);
}
