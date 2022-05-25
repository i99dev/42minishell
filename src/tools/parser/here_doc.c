/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:37:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 03:50:38 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*doc_get_heredoc(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
			j++;
		if (str[i] == '<' && str[i + 1] == '<')
		{
			while (str[i + 2] == ' ')
				i++;
			return (&str[i + 2]);
		}
		i++;
	}
	return (NULL);
}

void	doc_tmp_file(void)
{
	int		tmp_fd;

	tmp_fd = open("/tmp/minishell_tmp", O_RDONLY);
	unlink("/tmp/minishell_tmp");
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}

void	doc_line_doc(int temp_fd, char *eof)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
		{
			close(temp_fd);
			free(input);
			break ;
		}
		else
			ft_putendl_fd(input, temp_fd);
		free(input);
	}
}