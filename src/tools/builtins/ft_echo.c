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

char	*is_n(char *str, bool *flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (((str[0] == '-' && str[1] == 'n' && str[2] == ' ') || \
			(str[0] == '-' && str[1] == 'n' && str[2] == '\0') || \
			(str[0] == '-' && str[1] == 'n' && str[2] == 'n')) && !*flag)
		{
			i++;
			while ((str[i] == 'n') || (str[i] == '-' && str[i + 1] != 'n'))
			{
				i += 2;
				j = i;
				*flag = true;
			}
			while ((str[i] == ' ' || str[i] == '-' || str[i] == 'n'))
			{
				i++;
				j = i;
			}
		}
		i++;
	}
	if ((j == 0 || ((i - j) <= 1 && !*flag)) || (j == 8 && *flag))
		return (str);
	return (&str[j]);
}

void	ft_echo(t_minishell *msh, int i)
{
	bool	flag;
	int		j;
	int		k;

	flag = false;
	j = 1;
	while (msh->cmd_table[i].exec_table[j])
	{
		k = 0;
		msh->cmd_table[i].exec_table[1] = \
		is_n(msh->cmd_table[i].exec_table[1], &flag);
		while (msh->cmd_table[i].exec_table[j][k] == ' ' && flag)
			k++;
		ft_putstr_fd(&msh->cmd_table[i].exec_table[j][k], 1);
		j++;
	}
	if (flag == false)
		ft_putchar_fd('\n', 1);
}
