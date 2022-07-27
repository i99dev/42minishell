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

void	ft_redirect(t_minishell *msh, int i)
{
	int	j;

	j = 0;
	while (j < msh->cmd_table[i]->token_count)
	{
		if (!ft_strncmp(msh->cmd_table[i]->tok[j]->token, "<<", 2))
			here_doc(msh, i, j);
		else if (!ft_strncmp(msh->cmd_table[i]->tok[j]->token, ">>", 2))
			ft_redirect_append(msh, i, j);
		else if (!ft_strncmp(msh->cmd_table[i]->tok[j]->token, "<", 1))
			ft_redirect_in(msh, i, j);
		else if (!ft_strncmp(msh->cmd_table[i]->tok[j]->token, ">", 1))
			ft_redirect_out(msh, i, j);
		j++;
	}
}

void	execute_2(t_minishell *msh, int i)
{
	char			*path;

	ft_redirect(msh, i);
	path = get_path(msh, i);
	execve(path, msh->cmd_table[i]->exec_table, (char *const *)0);
	error_message(msh, "NOT FOUND", 127);
	msh->exit_status = 127;
	free(path);
	ft_free_prompt(msh);
	ft_command_table_free(msh);
	ft_free_minishell(msh);
}

void	execute(t_minishell *msh, int i)
{
	pid_t			pid;
	int				status;

	pid = fork();
	define_exec_signals(msh);
	if (pid < 0)
		err_msg("fork failed");
	if (pid == 0)
	{
		ft_redirect(msh, i);
		if (msh->cmd_table[i]->command_type == BUILTIN)
		{
			execute_builtin(msh, i);
			ft_free_prompt(msh);
			ft_command_table_free(msh);
			ft_free_minishell(msh);
		}
		else
			execute_2(msh, i);
	}
	waitpid(pid, &status, WUNTRACED);
	msh->exit_status = WEXITSTATUS(status);
}

bool	check_command_type(t_minishell *msh, int index)
{
	if (msh->cmd_table[index]->command_type == BUILTIN)
		return (true);
	else
		return (false);
}

void	init_execute(t_minishell *msh)
{
	int	i;

	i = 0;
	if (msh->command_count == 1)
	{
		if (ft_strncmp(msh->cmd_table[i]->exec_table[0], "echo", 5) && \
		msh->cmd_table[i]->command_type == BUILTIN)
			execute_builtin(msh, i);
		else
			execute(msh, 0);
	}
	else
		multi_pipe(msh, i);
}
