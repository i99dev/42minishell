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
//ft_strcut(char *str, char *in,int index)
void ft_strinsert(t_minishell *msh,char *str, char *in)
{
	(void)in;
	char *temp;
	char *tok;
	int i;
	int j;
	int k;
	/*
quote=$USER
unquote=DOCKER
msh->quote="$USER $HOME"*/
//copy everything before $
while(str[i] != '$')
{
	temp[i]=str[i];
	i++;
}
j=0;
//copy in
while(in[j])
{
	temp[i]=in[j];
	j++;
}
tok=ft_strchr(str,'$');
tok=ft_strtrim(tok,"$");
temp=find_hash(msh->env_table, tok);
printf("param %s\n",temp);
}
char *expand_parameters(t_minishell *msh, char *str)
{
	int i;
	char *temp_quote;
	char temp_param[100];

	i = 0;
	temp_quote=ft_strchr(str,'$');
	while(temp_quote)
	{
		i=0;
		//take everthing after $ and before ' ' or tab and replace it.
		//temp_param=temp_quote;
		while(temp_quote[i] != 0)
		{
			if (temp_quote[i] == ' ') // or tab
			break;
			if(i>0)
				temp_param[i-1]=temp_quote[i];
			i++;
		}
		temp_param[i-1]=0;
		//printf("FOUND %s param : %s len:%d\n",temp_quote, find_hash(msh->env_table, temp_param), i);
		temp_quote++;
		temp_quote=ft_strchr(temp_quote,'$');
	}
	return NULL;
	/*
	tmp = ft_strdup(*str);
	tmp = ft_without_quotes(tmp);
	free(*str);
	printf("tmp: %s\n", &tmp[1]);
	tmp = find_hash(msh->env_table, &tmp[1]);
	if (tmp)
		*str = ft_strdup(tmp);
	else
		*str = ft_strdup("");*/
}

void	ft_handle_double_quotes(t_minishell *msh)
{
	//char	*tmp;
	char	*temp;
	int i;
	int j;
	int k;
	k=0;
	i=0;
	//go through every cmd_table and check if any ""
	while(i < msh->command_count)
	{
		j=0;
		while(msh->cmd_table[i].cmd[j])
		{
			printf("finding quote\n");
			if(ft_strchr(msh->cmd_table[i].cmd[j],'\"'))
			{
				temp=ft_strchr(msh->cmd_table[i].cmd[j],'\"');
				if(temp[1] =='\"')
				{
				printf("found quote:%s\n",temp);
				msh->cmd_table[i].cmd[j]=NULL;
				expand_parameters(msh,msh->quotes[k]);
				msh->cmd_table[i].cmd[j]=ft_strdup(msh->quotes[k]);
				printf("after expand:%s i:%d j:%d\n",msh->cmd_table[i].cmd[j],i,j);
				k++;
				}
			}
			j++;
		}
		i++;
	}
	//expand quotes
	/*
	tmp = ft_strdup(*str);
	tmp = ft_without_quotes(tmp);
	free(*str);
	printf("tmp: %s\n", &tmp[1]);
	tmp = find_hash(msh->env_table, &tmp[1]);
	if (tmp)
		*str = ft_strdup(tmp);
	else
		*str = ft_strdup("");*/
}
int remove_quotes(t_minishell *msh, int start, int end, int q_index)
{
	//(void)msh;
	int i;
	char *temp;
	int len;
	int	len_q;
	int j;
	int k;
	int ret;
	len_q=end-start-1;
	len=ft_strlen(msh->line)-(end-start)+2;
	temp=malloc(sizeof(char) * (len));
	//copy everything before quote to temp
	i=0;
	while(i<=start)
	{
		temp[i]=msh->line[i];
		i++;
	}
	ret=i+1;
	j=i;
	msh->quotes[q_index]=malloc(sizeof(char)*len_q+1);
	//copy everything in quote to msh->quotes
	k=0;
	while(msh->line[i]!= DOUBLE_QUOTE)
	{
		msh->quotes[q_index][k]= msh->line[i];
		i++;
		k++;
	}
	msh->quotes[q_index][k]=0;
	i=end;
	//copy everything after quote to temp
	while(msh->line[i])
	{
		temp[j]=msh->line[i];
		i++;
		j++;
	}
	temp[j]=0;
	printf("start%d, end%d  ",start, end);
	//printf("\n new :%d\n",ft_strlen(msh->line)-(end-start)+2);
	printf("NEW LINE:%s strlen: %d\n",temp,ft_strlen(temp));
	printf("QUOTE:%s strlen: %d\n",msh->quotes[q_index],len_q);
	free(msh->line);
	msh->line=temp;
	printf("return:%d\n",ret);
	return (ret);

}
int		count_quotes(t_minishell *msh)
{
	int i;
	int count;
	int q_count;
	i=0;
	count=0;
	q_count=0;
	while (msh->line[i])
	{
		if( msh->line[i] == DOUBLE_QUOTE)
		{
			count++;
		}
		if (count==2)
		{
			q_count++;
			count=0;
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
	int j;

	msh->quote_count=count_quotes(msh);
	msh->quotes=malloc(sizeof(char *)*msh->quote_count+1);
	msh->quotes[msh->quote_count]=0;
	printf("Quote count: %d\n",msh->quote_count);
	i = 0;
	j = 0;
	count = 0;
	while (msh->line[i])
	{
		if( msh->line[i] == DOUBLE_QUOTE)
		{
			start = i;
			i++;
			while(msh->line[i] != DOUBLE_QUOTE)
				i++;
			if( msh->line[i] == DOUBLE_QUOTE)
			{
				end = i;
				count++;
			}
			count++;
		}
		if (count == 2)
		{
			//printf("start%d, end%d",start, end);
			i=remove_quotes(msh,start,end,j);
			j++;
			count=0;
		}
		i++;
	}
}
