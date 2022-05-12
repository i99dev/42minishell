/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:21:18 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/12 14:35:38 by oal-tena         ###   ########.fr       */
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

void	ft_redirect_in(t_minishell *msh, int index)
{
	int		fd;
	char	*file;

	file = check_file_name(msh->command_table[index], "<");
	printf("file: %s\n", file);
	fd = open(file, O_RDONLY | O_CREAT);
	if (fd == -1)
	{
		err_msg("minishell: no such file or directory: \n");
		return ;
	}
	msh->fd_std[index][STDIN_FILENO] = dup(STDIN_FILENO);
	close(fd);
}

void	ft_redirect_out(t_minishell *msh, int index)
{
	(void)msh;
	(void)index;
}

void	ft_doc_input(t_minishell *msh, int index)
{
	(void)msh;
	(void)index;
}
