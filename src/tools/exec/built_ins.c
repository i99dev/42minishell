/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:53 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/23 11:03:27 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	_execute_builtin(t_minishell *msh, int i)
{
	ft_redirect(msh, i);
	if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"echo", 5))
		ft_echo(msh, i);
	else if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"pwd", ft_strlen("pwd")))
		ft_pwd(msh);
	else if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"export", 7))
		ft_export(msh, i);
	else if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"unset", ft_strlen("unset")))
		ft_unset(msh, i);
	else if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"env", ft_strlen("env")))
		ft_env(msh, i);
	else if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"exit", 5))
		ft_exit(msh, i);
	else
		msh->exit_status = 127;
}

void	execute_builtin(t_minishell *msh, int i)
{
	if (!ft_strncmp(msh->cmd_table[i]->exec_table[0], \
	"cd", 3))
	{
		ft_cd(msh, i);
		return ;
	}
	_execute_builtin(msh, i);
}
