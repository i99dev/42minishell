/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:21:18 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/12 17:10:46 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strldup(const char *s1, int i)
{
	char	*str;

	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i--)
	{
		str[i] = s1[i];
	}
	return (str);
}

char	*check_file_name(char *str, char *token, int index)
{
	(void)index;
	int		j;
	int		len;

	j = 0;
	len =0;
	if (ft_strncmp(str, token, ft_strlen(token)) == 0)
	{
		while (j< ft_strlen(token))
		j++;
		if(str[ft_strlen(token)] && (str[ft_strlen(token)]== '>' || str[ft_strlen(token)]== '<'))
		{
			printf("parse error near %c\n",token[ft_strlen(token)]);
			//set error status and exit to next line
			return(NULL);
		}
		while(str[j] && (str[j]!= '>' && str[j]!= '<'))
		{
			len++;
			j++;
		}
	}
	return (ft_strldup(str+ ft_strlen(token), len));
}

void	ft_redirect_in(t_minishell *msh, int index, int token)
{
	int		fd;
	char	*file;

	file = msh->cmd_table[index].filename[token];
	fd = open(file, O_RDONLY | O_CREAT);
	if (fd == -1)
		error_message(msh, "redirect_in: no such file or directory", 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
void	ft_redirect_append(t_minishell *msh, int index, int token)
{
	int		fd;
	char	*file;

	file = msh->cmd_table[index].filename[token];
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			err_msg("minishell: no such file or directory: \n");
			return ;
		}
	}
	else
	{
		fd = open(file, O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			err_msg("minishell: no such file or directory: \n");
			return ;
		}
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	msh->rd++;
}

void	ft_redirect_out(t_minishell *msh, int index, int token)
{
	int		fd;
	char	*file;

	file = msh->cmd_table[index].filename[token];
	//printf("file: %s\n", file);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_message(msh, "redirect_out: no such file or directory", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	msh->rd++;
}

void	here_doc(t_minishell *msh, int i, int index)
{
	int		tmp_fd;
	char	*eof;

	tmp_fd = open("/tmp/minishell_tmp", \
	O_RDWR | O_CREAT | O_TRUNC, 0644);
	eof = msh->cmd_table[i].filename[index];
	//printf("eof:%s\n",eof);
	if (tmp_fd == -1)
	{
		err_msg("minishell: no such file or directory: \n");
		return ;
	}
	dup2(msh->fd_std[1], STDOUT_FILENO);
	doc_line_doc(msh, tmp_fd, eof);
	doc_tmp_file();
}
