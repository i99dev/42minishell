/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 04:12:35 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/21 04:21:49 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

typedef struct s_export
{
	int		j;
	int		k;
	char	*tmp;
	bool	has_export;
}				t_export;

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

void	init_export(t_export *export)
{
	export->j = 0;
	export->k = 0;
	export->tmp = NULL;
	export->has_export = false;
}

void	_check_export(t_minishell *msh, int i, t_export *ex)
{
	if (msh->cmd_table[i]->exec_table[ex->j][ex->k] == '+' || \
	(!ft_isalpha(msh->cmd_table[i]->exec_table[ex->j][ex->k]) \
	&& ex->k == 0))
	{
		msh->exit_status = 1;
		return ;
	}
	if (msh->cmd_table[i]->exec_table[ex->j][ex->k] == '=' && \
	ex->k != 0 && \
	msh->cmd_table[i]->exec_table[ex->j][ex->k + 1])
	{
		ex->tmp = ft_strsub(msh->cmd_table[i]->exec_table[ex->j], \
		0, ex->k);
		update_hash(msh, get_key_vlaue(ex->tmp), \
		msh->cmd_table[i]->exec_table[ex->j] + ex->k + 1);
		ex->has_export = true;
		free(ex->tmp);
	}
	else if (msh->cmd_table[i]->exec_table[ex->j][ex->k] == '=' && ex->k == 0)
		msh->exit_status = 1;
	else if (msh->cmd_table[i]->exec_table[ex->j][ex->k] == '=' && \
	!msh->cmd_table[i]->exec_table[ex->j][ex->k + 1] && !ex->has_export)
		msh->exit_status = 1;
	else if (msh->cmd_table[i]->exec_table[ex->j][ex->k] == '$' && ex->k == 0)
		msh->exit_status = 1;
}

void	ex_export_env(t_minishell *msh, int i)
{
	t_export	*ex;

	ex = (t_export *)malloc(sizeof(t_export));
	init_export(ex);
	ex->j = 1;
	while (msh->cmd_table[i]->exec_table[ex->j])
	{
		ex->k = 0;
		while (msh->cmd_table[i]->exec_table[ex->j][ex->k])
		{
			_check_export(msh, i, ex);
			ex->k++;
		}
		if (ex->k == ft_strlen(msh->cmd_table[i]->exec_table[ex->j]) && \
		!ex->has_export && ex->j > 1)
			msh->exit_status = 1;
		else if (msh->cmd_table[i]->exec_table[ex->j] && !ex->has_export)
		{
			update_hash(msh, msh->cmd_table[i]->exec_table[ex->j], "");
			ex->has_export = true;
		}
		ex->j++;
	}
}
