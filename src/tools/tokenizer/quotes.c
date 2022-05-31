/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 05:25:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/05/22 05:27:56 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
char	*ft_without_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 - 2));
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else
			new[j++] = str[i++];
	}
	return (new);
}
*/
char	*ft_strinsert(char *str, char *in)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	temp = malloc(sizeof(char) * 200);
	i = 0;
	while (str[i] != '$')
	{
		temp[i] = str[i];
		i++;
	}
	k = i;
	j = 0;
	while (in[j])
	{
		temp[i] = in[j];
		j++;
		i++;
	}
	while (str[k] != ' ' && str[k])
		k++;
	while (str[k])
	{
		temp[i] = str[k];
		k++;
		i++;
	}
	temp[i] = 0;
	return (temp);
}

char	*expand_parameters(t_minishell *msh, char *str)
{
	int		i;
	char	*temp_quote;
	char	*temp_param;

	i = 0;
	temp_quote = ft_strchr(str, '$');
	while (temp_quote)
	{
		i = 0;
		while (temp_quote[i] && temp_quote[i] != ' ')
			i++;
		temp_param = malloc(sizeof(char) * i);
		ft_strlcpy(temp_param, ++temp_quote, i);
		//printf("%s\n",find_hash(msh->env_table, temp_param));
		str = ft_strinsert(str, find_hash(msh->env_table, temp_param));
		free(temp_param);
		temp_quote++;
		temp_quote = ft_strchr(temp_quote, '$');
	}
	return (str);
}

void	ft_handle_double_quotes(t_minishell *msh)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	while (i < msh->command_count)
	{
		j = 0;
		while (msh->cmd_table[i].cmd[j])
		{
			if (ft_strchr(msh->cmd_table[i].cmd[j], '\"'))
			{
				temp = ft_strchr(msh->cmd_table[i].cmd[j], '\"');
				if (temp[1] == '\"')
				{
					free(msh->cmd_table[i].cmd[j]);
					msh->cmd_table[i].cmd[j] = ft_strdup(expand_parameters(msh, msh->quotes[k]));
				k++;
				}
			}
			j++;
		}
		i++;
	}
}

int	remove_quotes(t_minishell *msh, int start, int end, int q_index)
{
	int		i;
	char	*temp;
	int		len;
	int		len_q;
	int		j;
	int		k;
	int		ret;

	len_q = end - start - 1;
	len = ft_strlen(msh->line) - (end - start) + 2;
	temp = malloc(sizeof(char) * (len));
	i = 0;
	while (i <= start)
	{
		temp[i] = msh->line[i];
		i++;
	}
	ret = i + 1;
	j = i;
	msh->quotes[q_index] = malloc(sizeof(char) * len_q + 1);
	k = 0;
	while (msh->line[i] != DOUBLE_QUOTE)
	{
		msh->quotes[q_index][k] = msh->line[i];
		i++;
		k++;
	}
	msh->quotes[q_index][k] = 0;
	i = end;
	while (msh->line[i])
	{
		temp[j] = msh->line[i];
		i++;
		j++;
	}
	temp[j] = 0;
	free(msh->line);
	msh->line = temp;
	return (ret);
}

int	count_quotes(t_minishell *msh)
{
	int		i;
	int		count;
	int		q_count;

	i = 0;
	count = 0;
	q_count = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == DOUBLE_QUOTE)
			count++;
		if (count == 2)
		{
			q_count++;
			count = 0;
		}
		i++;
	}
	return (q_count);
}

void	ft_check_quotes(t_minishell *msh)
{
	int	i;
	int	start;
	int	end;
	int	count;
	int	j;

	msh->quote_count = count_quotes(msh);
	msh->quotes = malloc(sizeof(char *) * msh->quote_count + 1);
	msh->quotes[msh->quote_count] = 0;
	i = 0;
	j = 0;
	count = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == DOUBLE_QUOTE)
		{
			start = i;
			i++;
			while (msh->line[i] != DOUBLE_QUOTE)
				i++;
			if (msh->line[i] == DOUBLE_QUOTE)
			{
				end = i;
				count++;
			}
			count++;
		}
		if (count == 2)
		{
			i = remove_quotes(msh, start, end, j);
			j++;
			count = 0;
		}
		i++;
	}
}
