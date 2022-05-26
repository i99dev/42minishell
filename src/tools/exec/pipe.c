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
	waitpid(pid[i], NULL, 0);
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
		dup2(fd[i][1], 1);
		close(fd[i][1]);
		close(fd[i][0]);
	}
	if (i > 0)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
	}
	execve(get_path(msh, i), msh->cmd_table[i].exec_table, msh->env);
	if (i > 0)
		close(fd[i - 1][1]);
	perror("command failed");
}

// multi pips with loop and control pips close and open
void	multi_pipe(t_minishell *msh, int i)
{
	int		**fd;
	pid_t	*pid;

	fd = (int **)malloc(sizeof(int *) * (msh->command_count));
	pid = (pid_t *)malloc(sizeof(pid_t) * msh->command_count);
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
	free_pipe(&fd, &pid);
}
