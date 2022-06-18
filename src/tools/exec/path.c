/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 03:00:09 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/17 03:01:32 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	is_executable(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) != 0)
		return (false);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (false);
	if ((buffer.st_mode & S_IXUSR))
		return (true);
	return (false);
}

char	*get_path(t_minishell *msh, int command_table_index)
{
	char	*all_path;
	char	**tmp;
	char	*cmd;
	int		i;

	i = 0;
	cmd=ft_strdup("");
	//check if  exec first
	if (msh->cmd_table[command_table_index].exec_table[0][0] == '/' || msh->cmd_table[command_table_index].exec_table[0][0] == '.')
		return (ft_strdup(msh->cmd_table[command_table_index].exec_table[0]));
	all_path = find_hash(msh,msh->env_table, "PATH");
	//printf("cmd:%s",all_path);
	tmp = ft_split(all_path, ':');
	i = 0;
	while (tmp != NULL && tmp[i])
	{
		cmd = ft_strjoin(tmp[i], "/");
		cmd = ft_strjoin(cmd, \
		msh->cmd_table[command_table_index].exec_table[0]);
		if (is_executable(cmd))
			break ;
		free(cmd);
		cmd=ft_strdup("");
		i++;
	}
	return (cmd);
}
