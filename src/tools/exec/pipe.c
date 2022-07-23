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

void	close_pipe(t_minishell *msh, int (*fd)[2], int i, pid_t *pid)
{
	if (i <= msh->command_count - 1)
		close(fd[i][1]);
	if (i != 0)
		close(fd[i - 1][0]);
	(void) pid;
}

void	free_pipe(t_minishell *msh, int (*fd)[2], pid_t **pid)
{
	(void)msh;
	// int i;

	// i = 0;
	// // while (i < msh->command_count)
	// // {
	// // 	if((*fd)[i])
	// // 		free((*fd)[i]);
	// // 	i++;
	// // }
	free((*fd));
	free(*pid);
}

void	execute_pipe(t_minishell *msh, int i, int (*fd)[2], pid_t *pid)
{
	char	*path;

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
	ft_redirect(msh, i);
	if (msh->cmd_table[i]->command_type == BUILTIN)
	{
		if (ft_strncmp(msh->cmd_table[i]->exec_table[0], "cd", 3) || \
		ft_strncmp(msh->cmd_table[i]->exec_table[0], "exit", 5))
			execute_builtin(msh, i);
		free_pipe(msh, fd, &pid);
		ft_free_prompt(msh);
		ft_command_table_free(msh);
		ft_free_minishell(msh);
	}
	else
	{
		path = get_path(msh, i);
		execve(path, msh->cmd_table[i]->exec_table, NULL);
		error_message(msh, "NOT FOUND", 127);
		msh->exit_status = 127;
		free(path);
		free_pipe(msh, fd, &pid);
		ft_free_prompt(msh);
		ft_command_table_free(msh);
		ft_free_minishell(msh);
	}
}

void	_handle_loop(t_minishell *msh, int *i, pid_t *pid, int (*fd)[2])
{
	if (pipe(fd[*i]) == -1)
		perror("pipe");
	pid[*i] = fork();
	if (pid[*i] == -1)
		perror("fork");
	else if (pid[*i] == 0)
		execute_pipe(msh, *i, fd, pid);
	else
		close_pipe(msh, fd, *i, pid);
	(*i)++;
}

void	multi_pipe(t_minishell *msh, int i)
{
	int		(*fd)[2];
	pid_t	*pid;
	int		x;
	int		status;

	fd = malloc(sizeof(int [2]) * (msh->command_count));
	pid = (pid_t *)malloc(sizeof(pid_t) * msh->command_count);
	x = -1;
	while (i < msh->command_count)
		_handle_loop(msh, &i, pid, fd);
	while (++x < msh->command_count)
		waitpid(pid[x], &status, WUNTRACED);
	msh->exit_status = WEXITSTATUS(status);
	free_pipe(msh, fd, &pid);
}
