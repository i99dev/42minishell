/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 06:06:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 06:13:29 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool is_n(char *str)
{
	int	i;
	if (str[0] != '-')
		return false;
	i = 1;
	while (str[i] && str[i] == 'n')
			i++;
	if (i == ft_strlen(str) && i > 1)
		return (true);
	return (false);
}
bool check_n(t_minishell *msh, int i, int *j)
{
	while (msh->cmd_table[i].exec_table[*j] && is_n(msh->cmd_table[i].exec_table[*j]))
	{
		(*j)++;
	}
	if (*j > 1)
	 return true;
	return false;
}

void	ft_echo(t_minishell *msh, int i)
{
	bool	flag;
	int		j;

	flag = false;
	j = 1;

	if (check_n(msh, i, &j))
		flag = true;
	else if (msh->cmd_table[i].exec_table[1] && !msh->cmd_table[i].exec_table[2] && is_n(msh->cmd_table[i].exec_table[1]))
		return ;
	while (msh->cmd_table[i].exec_table[j])
	{
		printf("%s", msh->cmd_table[i].exec_table[j]);
		if (msh->cmd_table[i].exec_table[j + 1])
			printf(" ");
		j++;
	}
	if (!flag)
		printf("\n");
}
