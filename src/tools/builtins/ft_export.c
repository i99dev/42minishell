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
		has_export=false;
		k = 0;
		while (msh->cmd_table[i].exec_table[j][k])
		{
			if (msh->cmd_table[i].exec_table[j][k] == '=' && k != 0 && msh->cmd_table[i].exec_table[j][k+1])
			{
				tmp = ft_strsub(msh->cmd_table[i].exec_table[j], 0, k);
				update_hash(msh, get_key_vlaue(tmp), \
				msh->cmd_table[i].exec_table[j] + k + 1);
				has_export=true;
				free(tmp);
			}
			else if (msh->cmd_table[i].exec_table[j][k] == '=' && k == 0)
			msh->exit_status=1;
			else if (msh->cmd_table[i].exec_table[j][k] == '=' && !msh->cmd_table[i].exec_table[j][k+1])
			msh->exit_status=1;
			else if(msh->cmd_table[i].exec_table[j][k] == '$' && k==0)
			msh->exit_status=1;
			k++;
		}
		if (k==ft_strlen(msh->cmd_table[i].exec_table[j]) && !has_export && j > 1)
		msh->exit_status=1;
		j++;
	}
}


void	ft_export(t_minishell *msh, int i)
{
	if (msh->cmd_table[i].exec_table[1])
		export_env(msh, i);
	else 
	ft_env(msh,i);
}
