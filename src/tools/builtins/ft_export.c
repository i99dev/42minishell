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

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_key_vlaue(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	key = ft_strsub(str, 0, i);
	return (key);
}

void	export_env(t_minishell *msh, int i)
{
	int		j;
	int		k;
	char	*tmp;
	bool	has_export;

	j = 1;
	while (msh->cmd_table[i].exec_table[j])
	{
		has_export = false;
		k = 0;
		while (msh->cmd_table[i].exec_table[j][k])
		{
			if (msh->cmd_table[i].exec_table[j][k] == '+')
			{
				//ft_putstr_fd("not valid identifier",1);
				msh->exit_status = 1;
				return;
			}
			if (msh->cmd_table[i].exec_table[j][k] == '=' && k != 0 && msh->cmd_table[i].exec_table[j][k+1])
			{
				tmp = ft_strsub(msh->cmd_table[i].exec_table[j], 0, k);
				update_hash(msh, get_key_vlaue(tmp), \
				msh->cmd_table[i].exec_table[j] + k + 1);
				has_export=true;
				free(tmp);
			}
			else if (msh->cmd_table[i].exec_table[j][k] == '=' && k == 0)
			msh->exit_status = 1;
			else if (msh->cmd_table[i].exec_table[j][k] == '=' && !msh->cmd_table[i].exec_table[j][k+1] && !has_export)
			msh->exit_status = 1;
			else if(msh->cmd_table[i].exec_table[j][k] == '$' && k==0)
			msh->exit_status = 1;
			k++;
		}
		if (k==ft_strlen(msh->cmd_table[i].exec_table[j]) && !has_export && j > 1)
		msh->exit_status=1;
		j++;
	}
}

void print_export_vars(t_minishell *msh, int i)
{
	(void)i;

	unsigned int t_i;

	t_i = 0;
	while (t_i < msh->env_table->size)
	{
		if (msh->env_table->table[t_i])
		{
			ft_putstr_fd("export ",1);
			int j=0;
			ft_putstr_fd(msh->env_table->table[t_i]->key,1);
			ft_putchar_fd('=',1);
			ft_putchar_fd('\"',1);
			while(msh->env_table->table[t_i]->value[j])
			{
				if (msh->env_table->table[t_i]->value[j]=='\"')
				{
				ft_putchar_fd('\\',1);
				ft_putchar_fd('\"',1);
				}
				else if (msh->env_table->table[t_i]->value[j])
				ft_putchar_fd(msh->env_table->table[t_i]->value[j],1);
				j++;
			}
			ft_putchar_fd('\"',1);
			ft_putchar_fd('\n',1);
		}
		t_i++;
	}
}

void	ft_export(t_minishell *msh, int i)
{
	msh->exit_status=0;
	if (msh->cmd_table[i].exec_table[1])
		export_env(msh, i);
	else 
	print_export_vars(msh,i);
}