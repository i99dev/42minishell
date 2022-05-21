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

void	execute(t_minishell *msh, int i)
{
	pid_t			pid;
	int				status;
	char			*cmd;
	struct rusage	ru;

	cmd = get_path(msh, i);
	printf("cmd is :%s\n", cmd);
	printf("command_table is :%s\n", msh->command_table[i][0]);
	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		if (msh->token_count[i] != 0)
		{
			int j=0;
			while(j< msh->token_count[i])
			{
				printf("token count:%d\n",j);
			if (msh->token_ls[i]->token[j] == '>')
			{
				ft_redirect_out(msh, i, j);
			}
			else if (msh->token_ls[i]->token[j] == '<')
			{
				ft_redirect_in(msh, i, j);
			}
			j++;
			}
		}
		execve(cmd, msh->command_table[i], NULL);
		perror("command failed");
	}
	//close(msh->rd);
	wait4(pid, &status, 0, &ru);
}

bool	check_command_type(t_minishell *msh, int index)
{
	if (msh->command_type[index] == BUILTIN)
		return (true);
	else
		return (false);
}

void	init_execute(t_minishell *msh)
{
	int	i;

	i = 0;
	if (msh->token_count[i] > 0)
		printf("operator\n");
	while (i < msh->command_count)
	{
		int j=0;
		while (msh->command_table[i][j])
		{
			printf("%s\n", msh->command_table[i][j]);
			j++;
		}
		printf("token:%s\n",msh->token_ls[i]->token);
		i++;
	}
	i=0;
	if (msh->command_count == 1)
	{
		execute(msh, 0);
	}
	else
	{
		multi_pipe(msh, i);
	}
}
