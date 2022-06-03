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
	while (str[k] && str[k] != ' ' && str[k] != SINGLE_QUOTE)
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
		while (temp_quote[i] && temp_quote[i] != ' ' && temp_quote[i] != SINGLE_QUOTE)
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
	char	*temp_d;
	char	*temp_s;
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
			while(k<msh->quote_count && (ft_strchr(msh->cmd_table[i].cmd[j], '\"') || ft_strchr(msh->cmd_table[i].cmd[j], '\'')))
			{
				if (ft_strchr(msh->cmd_table[i].cmd[j], '\"'))
				{
					temp_d = ft_strdup(ft_strchr(msh->cmd_table[i].cmd[j], '\"'));
					if (temp_d[1] && temp_d[1] == '\"')
					{
						msh->cmd_table[i].cmd[j][ft_strlen(msh->cmd_table[i].cmd[j]) - ft_strlen(temp_d)] = 0;
						msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j],expand_parameters(msh, msh->quotes[k]));
						msh->cmd_table[i].cmd[j]=ft_strjoin(msh->cmd_table[i].cmd[j],temp_d+2);
						free(temp_d);
						k++;
					}
					else
					break;
				}
				else if (ft_strchr(msh->cmd_table[i].cmd[j], '\''))
				{
					temp_s = ft_strdup(ft_strchr(msh->cmd_table[i].cmd[j], '\''));
					if (temp_s[1] && temp_s[1] == '\'')
					{
						msh->cmd_table[i].cmd[j][ft_strlen(msh->cmd_table[i].cmd[j]) - ft_strlen(temp_s)] = 0;
						if(msh->quotes)
						msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j], msh->quotes[k]);
						msh->cmd_table[i].cmd[j] = ft_strjoin(msh->cmd_table[i].cmd[j], temp_s + 2);
						free (temp_s);
					k++;
					}
					else
					break;
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
	while (i<end)
	{
		msh->quotes[q_index][k] = msh->line[i];
		i++;
		k++;
	}
	msh->quotes[q_index][k] = 0;
	//printf("quote%d:%s\n",q_index,msh->quotes[q_index]);
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
	//printf("msh->line:%s start%d end%d ret%d\n ",temp,start,end,ret);
	return (ret);
}

int	count_quotes(t_minishell *msh)
{
	int		i;
	int		first_quote;
	int		q_count;

	i = 0;
	q_count = 0;
	first_quote = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == DOUBLE_QUOTE && first_quote == 0)
			first_quote = DOUBLE_QUOTE;
		else if (msh->line[i] == SINGLE_QUOTE && first_quote == 0)
			first_quote = SINGLE_QUOTE;
		i++;
		if (msh->line[i] && msh->line[i] == first_quote)
		{
			q_count++;
			first_quote = 0;
			i++;
		}
	}
	return (q_count);
}

void	ft_check_quotes(t_minishell *msh)
{
	int	i;
	int	start;
	//int	end;
	int	first_quote;
	int	j;

	msh->quote_count = count_quotes(msh);
	msh->quotes = malloc(sizeof(char *) * msh->quote_count + 1);
	msh->quotes[msh->quote_count] = 0;
	i = 0;
	j = 0;
	first_quote = 0;
	while (msh->line[i])
	{
		if ((msh->line[i] == DOUBLE_QUOTE || msh->line[i] == SINGLE_QUOTE) && first_quote == 0)
		{
			first_quote = msh->line[i];
			start = i;
		}
		i++;
		if (msh->line[i] && msh->line[i] == first_quote)
		{
			i = remove_quotes(msh, start, i, j);
			j++;
			first_quote = 0;
		}
	}
}
