#include "../../../include/minishell.h"

void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			close(oldfd);
		else
			perror("dup2");
	}
}

/*  
source : https://gist.github.com/zed/7835043
TODO:	add error_msg for pipe and fork errors
		fix exit when error in child process ..ls | grep | echo hi

*/
void	pipe_recursive(t_minishell *msh, int i, int in_fd)
{
	pid_t	pid;
	int		fd[2];

	if (i == msh->token_count - 1)
		execute(msh, i);
	else
	{
		if (pipe(fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			close(fd[0]);
			redirect(in_fd, STDIN_FILENO);
			redirect(fd[1], STDOUT_FILENO);
			execve(msh->command_table[i][0], msh->command_table[i], NULL);
			perror("command failed");
		}
		else
			pipe_recursive(msh, i + 1, fd[0]);
	}
}

/*
 temporary function 
 */
void	execute_pipe(t_minishell *msh, int i)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		status;

	pipe(fd);
	while (msh->command_table[i])
	{}
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