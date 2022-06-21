/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 06:16:06 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/25 06:16:16 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	_print_value(t_minishell *msh, unsigned int t_i, int *j)
{
	if (msh->env_table->table[t_i]->value[*j])
	{
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
	}
	while (msh->env_table->table[t_i]->value[*j])
	{
		if (msh->env_table->table[t_i]->value[*j] == '\"')
		{
			ft_putchar_fd('\\', 1);
			ft_putchar_fd('\"', 1);
		}
		else if (msh->env_table->table[t_i]->value[*j])
			ft_putchar_fd(msh->env_table->table[t_i]->value[*j], 1);
		*j = *j + 1;
	}
}

void	print_export_vars(t_minishell *msh, int i)
{
	int				j;
	unsigned int	t_i;

	t_i = 0;
	(void)i;
	while (t_i < msh->env_table->size)
	{
		if (msh->env_table->table[t_i])
		{
			ft_putstr_fd("export ", 1);
			j = 0;
			ft_putstr_fd(msh->env_table->table[t_i]->key, 1);
			_print_value(msh, t_i, &j);
			if (msh->env_table->table[t_i]->value[0])
				ft_putchar_fd('\"', 1);
			ft_putchar_fd('\n', 1);
		}
		t_i++;
	}
}

void	ft_export(t_minishell *msh, int i)
{
	msh->exit_status = 0;
	if (msh->cmd_table[i]->exec_table[1])
		ex_export_env(msh, i);
	else
		print_export_vars(msh, i);
}
