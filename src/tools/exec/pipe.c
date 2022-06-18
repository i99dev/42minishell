/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:00:17 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/24 11:00:17 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	close_pipe(t_minishell *msh, int **fd, int i, pid_t *pid)
{
	if (i <= msh->command_count - 1)
		close(fd[i][1]);
	if (i != 0)
		close(fd[i - 1][0]);
	(void) pid;
	// waitpid(pid[i], NULL, 0);
}

void	free_pipe(int ***fd, pid_t **pid)
{
	free((*fd));
	free(*pid);
}

void	execute_pipe(t_minishell *msh, int i, int **fd)
{
	ft_redirect(msh, i);
	if (i != msh->command_count - 1)
	{
		//printf("i != cmdcount-1  command is %s and i = %d\n",msh->cmd_table->exec_table[i], i);
		dup2(fd[i][1], 1);
		close(fd[i][1]);
		close(fd[i][0]);
	}
	if (i > 0)
	{
		//printf("i>0 command is %s and i = %d\n",msh->cmd_table->exec_table[i], i);
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
	}
	if(msh->cmd_table[i].command_type == BUILTIN)
	{
		execute_builtin(msh, i);
		exit(0);
	}
	else
	{
	execve(get_path(msh, i), msh->cmd_table[i].exec_table, msh->env);
	error_message(msh, "command not found", 127);
	exit(127);
	}
}

// multi pips with loop and control pips close and open
void	multi_pipe(t_minishell *msh, int i)
{
	int		**fd;
	pid_t	*pid;
	int		x;
	int		status;

	fd = (int **)malloc(sizeof(int *) * (msh->command_count));
	pid = (pid_t *)malloc(sizeof(pid_t) * msh->command_count);
	x = -1;
	while (i < msh->command_count)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
			perror("pipe");
		pid[i] = fork();
		if (pid[i] == -1)
			perror("fork");
		else if (pid[i] == 0)
			execute_pipe(msh, i, fd);
		else
			close_pipe(msh, fd, i, pid);
		i++;
	}
	while (++x < msh->command_count)
		waitpid(pid[x], &status, 0);
	msh->exit_status = WEXITSTATUS(status);
	free_pipe(&fd, &pid);
}
