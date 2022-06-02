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

	while (j < msh->cmd_table[i].token_count)
	{
		if (!ft_strncmp(msh->cmd_table[i].tok[j].token, "<<", 2))
			here_doc(msh, i, j);
		else if (!ft_strncmp(msh->cmd_table[i].tok[j].token, ">>", 2))
		{
			//printf("double");
			ft_redirect_append(msh, i, j);
		}
		else if (!ft_strncmp(msh->cmd_table[i].tok[j].token, "<", 1))
			ft_redirect_in(msh, i, j);
		else if (!ft_strncmp(msh->cmd_table[i].tok[j].token, ">", 1))
			ft_redirect_out(msh, i, j);
		j++;
	}
}

void	execute(t_minishell *msh, int i)
{
	pid_t			pid;
	int				status;
	struct rusage	ru;
	char			*cmd;

	pid = fork();
	if (pid < 0)
	{
		err_msg("fork failed");
	}
	else if (pid == 0)
	{
		ft_redirect(msh, i);
		cmd = get_path(msh, i);
		//printf("path %s\n",cmd);
		execve(cmd, msh->cmd_table[i].exec_table, msh->env);
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

void	execute_builtin(t_minishell *msh, int i)
{
	ft_redirect(msh, i);
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"echo", ft_strlen("echo")))
		ft_echo(msh, i);
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"cd", ft_strlen("cd")))
		ft_cd(msh, i);
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"pwd", ft_strlen("pwd")))
		ft_pwd();
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"export", ft_strlen("export")))
		ft_export(msh, i);
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"unset", ft_strlen("unset")))
		ft_unset(msh, i);
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"env", ft_strlen("env")))
		ft_env(msh, i);
	if (!ft_strncmp(msh->cmd_table[i].cmd[0], \
	"exit", ft_strlen("exit")))
		ft_exit(msh, i);
}

void	init_execute(t_minishell *msh)
{
	int	i;

	i = 0;
	if (msh->command_count == 1 && msh->cmd_table[i].command_type != BUILTIN)
	{
		//printf("1 command\n");
		//printf("%s\n%s\n",msh->cmd_table[i].exec_table[0],msh->cmd_table[i].exec_table[1]);
		execute(msh, 0);
	}
	else if (msh->cmd_table[i].command_type == BUILTIN)
		execute_builtin(msh, i);
	else
	{
		multi_pipe(msh, i);
	}
}
