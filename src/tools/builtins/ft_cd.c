/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:32:21 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 06:12:42 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	_2path(t_minishell *msh, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	update_hash(msh, "OLDPWD", pwd);
	if (chdir(path) == -1)
	{
		error_message(msh, "cd: no such file or directory", 1);
		ft_putendl_fd(path, 2);
		free(pwd);
		return ;
	}
	free(pwd);
	pwd = getcwd(NULL, 0);
	update_hash(msh, "PWD", pwd);
	free(pwd);
}

void	cd_to_home(t_minishell *msh)
{
	char	*path;

	path = find_hash(msh, msh->env_table, "HOME");
	if (path == NULL)
	{
		error_message(msh, "cd: no home directory", 1);
		return ;
	}
	_2path(msh, path);
	free(path);
}

void	ft_cd(t_minishell *msh, int i)
{
	msh->exit_status = 0;
	if (msh->cmd_table[i]->exec_table[1] == NULL || \
	!ft_strncmp(msh->line, "~", 2))
		cd_to_home(msh);
	else if (!ft_strncmp(msh->cmd_table[i]->exec_table[1], "-", ft_strlen("-")))
	{
		if (find_hash(msh, msh->env_table, "OLDPWD") == NULL)
		{
			error_message(msh, "cd: OLDPWD not set", 1);
			return ;
		}
		_2path(msh, ft_strdup(find_hash(msh, msh->env_table, "OLDPWD")));
	}
	else
		_2path(msh, msh->cmd_table[i]->exec_table[1]);
	//ft_command_table_free(msh);
}
