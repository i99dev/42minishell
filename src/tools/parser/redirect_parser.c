/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:21:18 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/23 16:43:12 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*check_file_name(char **str, char *token, int index)
{
	int		j;

	j = 0;
	if (ft_strncmp(str[index], token, ft_strlen(token)) == 0)
	{
		j++;
		/*
		while (ft_strncmp(&str[index][j], token, ft_strlen(token)) == 0)
		j++;*/
		while (str[index][j] == ' ' || str[index][j] == '\t')
			j++;
		if (str[index][j])
			return (&str[index][j]);
	}
	/*
	if (str[1] == NULL)
		return (ft_strchr(str[0], token[0]) + 1);*/
	return (NULL);
}

void	ft_redirect_in(t_minishell *msh, int index,int token)
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
	}/*
	if(msh->rd>0)
	{
		dup2(fd, msh->last_fd);
		close(fd);
		msh->last_fd=fd;
		msh->rd++;
	}
	else
	{
		*/
	dup2(fd, STDOUT_FILENO);
	close(fd);
	msh->rd++;
	
}

void	here_doc(t_minishell *msh, int index)
{
	(void)msh;
	(void)index;
}
