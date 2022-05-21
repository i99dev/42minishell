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

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	free_pipe(int ***fd, pid_t **pid)
{
	//int	i;

	//i = 0;
	/*
	while((*fd)[i])
	{
		free((*fd)[i]);
		i++;
	}*/
	free((*fd));
	free(*pid);
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
		{
			if (i == 0 && msh->token_ls[i] != NULL)
			{
				if (ft_strncmp(msh->token_ls[i]->token, "<", 1) == 0)
					ft_redirect_in(msh, i);
			}
			if (i == msh->command_count - 1 && msh->token_ls[i] != NULL)
			{
				if (ft_strncmp(msh->token_ls[i]->token, ">", 1) == 0)
					ft_redirect_out(msh, i);
			}
			if (i != msh->command_count - 1)
			{
				dup2(fd[i][1], 1);
				close(fd[i][1]);
				close(fd[i][0]);
				printf("YES");
			}
			if (i > 0)
			{
				dup2(fd[i - 1][0], 0);
				close(fd[i - 1][0]);
			}
			execve(get_path(msh, i), msh->command_table[i], __environ);
			if (i > 0)
				close(fd[i - 1][1]);
			perror("command failed");
		}
		else
		{
			if (i <= msh->command_count - 1)
				close(fd[i][1]);
			if (i != 0)
				close(fd[i - 1][0]);
			waitpid(pid[i], NULL, 0);
		}
		i++;
	}
	free_pipe(&fd, &pid);
	//waitpid(pid, NULL, 0);
}
