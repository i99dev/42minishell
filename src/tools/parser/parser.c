/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:21:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/21 04:54:28 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	here_doc(t_minishell *msh, int i, int index)
{
	int		tmp_fd;
	char	*eof;

	tmp_fd = open("/tmp/minishell_tmp", \
	O_RDWR | O_CREAT | O_TRUNC, 0644);
	eof = msh->cmd_table[i]->filename[index];
	if (tmp_fd == -1)
	{
		err_msg("minishell: no such file or directory: \n");
		return ;
	}
	if (msh->cmd_table[index]->exec_table[0])
	{
		dup2(msh->fd_std[1], STDOUT_FILENO);
		doc_line_doc(msh, tmp_fd, eof);
		doc_tmp_file();
	}
}
