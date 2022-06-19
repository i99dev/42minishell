/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:26:31 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/06 02:14:29 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * @brief we need funcation split all word wit index and next joint word
 * 
 */

bool	is_case_alph(char str)
{
	if (str >= 'a' && str <= 'z')
		return (true);
	if (str >= 'A' && str <= 'Z')
		return (true);
	if (str >= '0' && str <= '9')
		return (true);
	if (str == '?' || str == '\"' || str == '\'')
		return true;
	return (false);
}

char	*get_key_from_str(t_minishell *msh, char *str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (isalpha(str[i]) || str[i]=='?')
	{
		key[i] = str[i];
		if(str[i++]=='?')

			break ;
	}
	key[i] = '\0';
	if ((key[0] != '\0' && !isdigit(str[i])))
	{
		value = find_hash(msh,msh->env_table, key);
		//printf("%s %s\n",value,key);
		if (value)
			key = ft_strdup(value);
		else
			key = ft_strdup("");
		key = ft_strjoin(key, &str[i]);
	}
	else if (isdigit(str[i]) && i==0)
		return ft_strdup(str + 1);
	else if(isdigit(str[i]))
		return ft_strdup("");
	else
		key = ft_strdup(str);
	return (key);
}
bool is_parameter(char *str)
{
	char *tmp;

	tmp=ft_strchr(str, '$');
	if(tmp)
	{
		tmp=ft_strdup(tmp);
	if(tmp[1] && tmp[1]==' ' && ft_strchr(&tmp[1],'$'))
		return true;
	if ((tmp[1] && !is_case_alph(tmp[1]) && tmp[1]!= ' ')|| ft_strlen(tmp) == 1)
	return false;
	}
	else
	return false;
	return true;
}
char	*expand_cmd(t_minishell *msh, char *str)
{
	char	*tmp;
	char	*start;
	char	*res;
	int		i;
	int		len;
	//int 	last_i;

	start = ft_strchr(str, '$');
	if (!start)
		return (str);
	if(start[1] && start[1] == ' ')
			;
	else if(!start[1] || (!is_case_alph(start[1]) && !special_char_with_dollar(start)))
		return str;
	i = 0 ;
	//last_i = 0;
	len = ft_strlen(str) - ft_strlen(start);
	res = (char *)malloc(sizeof(char) * 1024);
	while (is_parameter(&start[i]))
	{
		while (start [i] && start[i] != '$')
		{
			i++;
		}
		if(start[i+1] && start[i+1] == ' ')
		{
			if(start[i+2])
			{
			i+=2;
			continue;
			}
			else
			break;
		}
		tmp = ft_strjoin(ft_substr(start, 0, i), \
		get_key_from_str(msh, &start[i + 1]));
		//printf("%s\n",tmp);
		start = tmp;
	}
	start=ft_strdup(start);
	i = 0;
	str[len]=0;
	/*
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}*/
	res = ft_strjoin(str, start);
	return (res);
}
