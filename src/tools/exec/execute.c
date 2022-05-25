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
	struct rusage	ru;
	int				j;

	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		msh->rd = 0;
		if (msh->cmd_table[i].token_count != 0)
		{
			j = 0;
			while (j < msh->cmd_table[i].token_count)
			{
				printf("token count:%d\n", j);
				if (!ft_strncmp(msh->cmd_table[i].tok[j].token, ">", 2))
					ft_redirect_out(msh, i, j);
				else if (!ft_strncmp(msh->cmd_table[i].tok[j].token, ">>", 3))
					ft_redirect_out(msh, i, j);
				else if (!ft_strncmp(msh->cmd_table[i].tok[j].token, "<", 2))
					ft_redirect_in(msh, i, j);
				else if (!ft_strncmp(msh->cmd_table[i].tok[j].token, "<<", 3))
					here_doc(msh);
			j++;
			}
		}
		execve(get_path(msh, 0), msh->cmd_table[i].exec_table, msh->env);
		perror("command failed");
	}
	wait4(pid, &status, 0, &ru);
}

bool	check_command_type(t_minishell *msh, int index)
{
	if (msh->cmd_table[index].command_type == BUILTIN)
		return (true);
	else
		return (false);
}

void	init_execute(t_minishell *msh)
{
	int	i;

	i = 0;
	if (msh->cmd_table[i].token_count > 0)
		printf("operator\n");
	while (i < msh->command_count)
	{
		int j=0;
		while (msh->cmd_table[i].exec_table[j])
		{
			printf("%s\n", msh->cmd_table[i].exec_table[j]);
			j++;
		}
		j=0;
		while(j<msh->cmd_table[i].token_count)
		{
		printf("token:%s\nfilename:%s\n",msh->cmd_table[i].tok[j].token,msh->cmd_table[i].filename[j]);
		j++;
		}
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
