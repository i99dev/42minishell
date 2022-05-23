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
	all_path = find_hash(msh->env_table, "PATH");
	tmp = ft_split(all_path, ':');
	while (tmp[i])
	{
		cmd = ft_strjoin(tmp[i], "/");
		cmd = ft_strjoin(cmd, msh->command_table[command_table_index][0]);
		if (is_executable(cmd))
			break ;
		i++;
	}
	i = 0;
	return (cmd);
}