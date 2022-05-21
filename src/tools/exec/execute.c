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
	printf("command_table is :%s\n", msh->command_table[i][1]);
	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		if (msh->token_ls[0] != NULL)
			{
				if (ft_strncmp(msh->token_ls[i]->token, ">", 1) == 0)
					ft_redirect_out(msh, i);
				if (ft_strncmp(msh->token_ls[i]->token, "<", 1) == 0)
					ft_redirect_in(msh, i);
			}
		execve(cmd, msh->command_table[i], NULL);
		perror("command failed");
	}
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
	if (check_command_type(msh, i))
	{
		return ;
	}
	if (msh->command_count>1)
	{
	multi_pipe(msh, i);
	}
	else
	{
		execute(msh,0);
	}
}
