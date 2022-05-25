/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:21:18 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 04:45:43 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*check_file_name(char **str, char *token)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], token, ft_strlen(token)) == 0)
		{
			j = 0;
			while (ft_strncmp(&str[i][j], token, ft_strlen(token)) == 0)
				j++;
			while (str[i][j] == ' ' || str[i][j] == '\t')
				j++;
			if (str[i][j])
				return (&str[i][j]);
		}
		i++;
	}
	if (str[1] == NULL)
		return (ft_strchr(str[0], token[0]) + 1);
	return (str[i - 1]);
}

void	ft_redirect_in(t_minishell *msh, int index, int token)
{
	int		fd;
	char	*file;

	file = msh->cmd_table[index].filename[token];
	printf("file: %s\n", file);
	fd = open(file, O_RDONLY | O_CREAT);
	if (fd == -1)
	{
		err_msg("minishell: no such file or directory: \n");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_redirect_out(t_minishell *msh, int index, int token)
{
	int		fd;
	char	*file;

	file = msh->cmd_table[index].filename[token];
	printf("file: %s\n", file);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		err_msg("minishell: no such file or directory: \n");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	msh->rd++;
}

void	here_doc(t_minishell *msh)
{
	int		tmp_fd;
	char	*eof;

	tmp_fd = open("/tmp/minishell_tmp", \
	O_RDWR | O_CREAT | O_TRUNC, 0644);
	eof = doc_get_heredoc(msh->line);
	if (tmp_fd == -1)
	{
		err_msg("minishell: no such file or directory: \n");
		return ;
	}
	dup2(msh->fd_std[1], STDOUT_FILENO);
	doc_line_doc(tmp_fd, eof);
	doc_tmp_file();
}
