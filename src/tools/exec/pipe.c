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

void	pipe_recursive(t_minishell *msh, int i, int in_fd)
{
	pid_t	finalpid;
	int		status;

	if (msh->command_seq[i] == 0)
	{
		redirect(in_fd, STDIN_FILENO);
		finalpid = fork();
		if (finalpid == 0)
		{
			execve(msh->command_table[i][0], msh->command_table[i], NULL);
			perror("command failed");
		}
		//close(in_fd);
		waitpid(finalpid, &status, WUNTRACED);
	}
	else
	{
		int	fd[2];
		pid_t pid;
		if (pipe(fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("pipe");
		else if (pid == 0)
		{
			close(fd[0]);
			redirect(in_fd, STDIN_FILENO);
			redirect(fd[1], STDOUT_FILENO);
			execve(msh->command_table[i][0], msh->command_table[i], NULL);
			perror("execve");
		}
		else
		{
			close(fd[1]);
			close(in_fd);
			pipe_recursive(msh, i + 1, fd[0]);
		}
	}
}