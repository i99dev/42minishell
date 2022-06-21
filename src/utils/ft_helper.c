/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 05:56:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/21 10:04:30 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_user_info(t_minishell *msh)
{
	char	*user;
	char	*host;
	char	*tmp;

	tmp = NULL;
	user = find_hash(msh,msh->env_table, "USER");
	if (!user)
		user = "root";
	host = getenv("HOSTNAME");
	if (!host)
		host = "localhost";
	tmp = ft_strjoin(tmp, BLUE"["GREEN);
	tmp = ft_strjoin(tmp, user);
	tmp = ft_strjoin(tmp, RED"@"GREEN);
	tmp = ft_strjoin(tmp, host);
	tmp = ft_strjoin(tmp, BLUE"]");
	tmp = ft_strjoin(tmp, ":");
	tmp = ft_strjoin(tmp, getcwd(NULL, 0));
	tmp = ft_strjoin(tmp, RED"> "RESET);
	return (tmp);
}

bool	is_token(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (true);
	else if (str[0] == '>')
		return (true);
	else if (str[0] == '<')
		return (true);
	return (false);
}
