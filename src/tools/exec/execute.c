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

/*  
source : https://gist.github.com/zed/7835043
*/
void	execute_pipe_recursive(t_minishell *msh, int i, int in_fd)
{
	int		fd[2];
	pid_t	childpid;
	//pid_t	finalpid;
	//int		status;

	if (i == msh->token_count - 1)
	{ /*last command */
		execute(msh, i);
		/*
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) != -1)
				close(in_fd);
			else
				ft_free_minishell(msh);
		}
		//finalpid = fork();
		//if (finalpid==0)
		//{
			execve(msh->command_table[i][0], msh->command_table[i], NULL);
			perror("command failed");
			exit(1);
		//}
		//close(fd[0]);
		//close(in_fd);
		//close(fd[1]);
		//waitpid(finalpid, &status, WUNTRACED);*/
	}
	else
	{
		if ((pipe(fd) == -1) || ((childpid = fork()) == -1))
			exit(1);
		if (childpid == 0)
		{ /* child executes current command */
			close(fd[0]);
			if (dup2(in_fd, STDIN_FILENO) == -1) /*read from in_fd */
				perror("Failed to redirect stdin");
			if (dup2(fd[1], STDOUT_FILENO) == -1)   /*write to fd[1]*/
				perror("Failed to redirect stdout");
			else if ((close(fd[1]) == -1))
				perror("Failed to close extra pipe descriptors");
			else
			{
				execve(msh->command_table[i][0], msh->command_table[i], NULL);
				exit(1);
			}
		}
		//close(fd[1]);   /* parent executes the rest of commands */
		//close(in_fd);
		execute_pipe_recursive(msh, i + 1, fd[0]);
	}
}

/*
	TODO : error hamdling for pipe and fork and dup2 functions
		   make this function recursive !!
*/
void	execute_pipe(t_minishell *msh, int i)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		status;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execve(msh->command_table[i][0], msh->command_table[i], NULL);
		exit(1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		execve(msh->command_table[i + 1][0], msh->command_table[i + 1], NULL);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, WUNTRACED);
	waitpid(pid2, &status, WUNTRACED);
}

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
	TODO: check whether command is bin or builtin command
		  check if command_seq is pipe or redirect or single command.
		  make recursive
*/
void	init_execute(t_minishell *msh)
{
	int	i;

	if (msh->token_count > 0)
		add_bin_path(msh, 0);
	if (msh->token_count == 1)
		execute(msh, 0);
	else if (msh->token_count == 2)
	{
		add_bin_path(msh, 1);
		execute_pipe(msh, 0);
	}
	else if (msh->token_count > 2)
	{
		i = 1;
		while (i < msh->token_count)
		{
			add_bin_path(msh, i);
			i++;
		}
		execute_pipe_recursive(msh, 0, STDIN_FILENO);
	}
}

void	execute(t_minishell *msh, int i)
{
	pid_t			pid;
	int				status;
	struct rusage	ru;

	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		execve(msh->command_table[i][0], msh->command_table[i], __environ);
		perror("command failed");
		exit(1);
	}
	wait4(pid, &status, 0, &ru);
}
