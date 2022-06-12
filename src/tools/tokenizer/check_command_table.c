/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:25:29 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/12 17:09:42 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


char	*get_io_filename(t_minishell *msh, int i, char *token, int index)
{
	(void)token;
	//is  it alone
	if (is_token(msh->cmd_table[i].cmd[index]) && \
	ft_strlen(msh->cmd_table[i].cmd[index]) <= 2)
	{
		//printf("redirect with space\n");
		return (ft_strdup(msh->cmd_table[i].cmd[index + 1]));
	}
	//it is between a string
	//it is 
	else
		return (NULL);
}

void	alloc_cmd(t_minishell *msh, int i, char ***exec, t_token **tok, char ***filename)
{
	*exec = (char **)malloc(sizeof(char *) * (msh->cmd_table[i].arg_count + 1));
	*tok = (t_token *)malloc(sizeof(t_token) * msh->cmd_table[i].token_count + 1);
	*filename = (char **)malloc(sizeof(char *) * msh->cmd_table[i].token_count + 1);
}

bool	is_token(char *str)
{
	if (ft_strchr(str, '<') != NULL)
		return (true);
	else if (ft_strchr(str, '>') != NULL)
		return (true);
	return (false);
}
/*
support str ls>out>>out1>out2

while strchr(>)
if len 0 means  arg
if len = str means token at start token/s
else means arg at start and token  arg + token/s

*/
void	count_token(t_minishell *msh, int i)
{
	int		index;
	char	*temp;

	index = 0;

	msh->cmd_table[i].token_count = 0;
	msh->cmd_table[i].arg_count = 0;
	while (msh->cmd_table[i].cmd[index])
	{
		temp=ft_strchr(msh->cmd_table[i].cmd[index],'>');
		if (!temp)
		{
			msh->cmd_table[i].arg_count++;
		}
		else if(ft_strlen(temp)==1)
		{
			index++;
			if(index>msh->cmd_table->cmd_count)
			break;
		}
		else if(ft_strlen(temp) < ft_strlen(msh->cmd_table[i].cmd[index]))
		{
			msh->cmd_table[i].arg_count++;
		}
		while(temp)
		{
			msh->cmd_table[i].token_count++;
			if(temp+1)
			temp=ft_strchr(temp+1,  '>');
		}
	/*
		//is token with space
		if (is_token(msh->cmd_table[i].cmd[index]) && \
			ft_strlen(msh->cmd_table[i].cmd[index]) <= 2)
		{
			msh->cmd_table[i].token_count++;
			//if  the next one is file name skip
			if (msh->cmd_table[i].cmd[index + 1] && \
				!is_token(msh->cmd_table[i].cmd[index + 1]))
			{
				index += 2;
				continue ;
			}
		}
		//else its a token without  space
		else if (is_token(msh->cmd_table[i].cmd[index]))
			msh->cmd_table[i].token_count++;
		else
			msh->cmd_table[i].arg_count++;*/
		index++;
	}
	//printf("token count:%d\narg count:%d",msh->cmd_table[i].token_count,msh->cmd_table[i].arg_count);
	alloc_cmd(msh,i,&msh->cmd_table[i].exec_table, &msh->cmd_table[i].tok, &msh->cmd_table[i].filename);
	
	msh->cmd_table[i].exec_table[msh->cmd_table[i].arg_count] = NULL;
	msh->cmd_table[i].tok[msh->cmd_table[i].token_count].token = NULL;
	msh->cmd_table[i].filename[msh->cmd_table[i].token_count] = NULL;
}
/*
static int	tk_handle_redirect_in(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
	msh->cmd_table[i].tok[*j].token = ft_strdup("<");
	msh->cmd_table[i].filename[*j] = \
	get_io_filename(msh, i, "<", index);
	(*j)++;
	if (*j == 1)
		wordindex = index;
	return (wordindex);
}
*/
/*
static int	tk_handle_redirect_out(t_minishell *msh, int i, int *j, int index)
{
	int		wordindex;

	wordindex = 0;
	
	msh->cmd_table[i].tok[*j].token = ft_strdup(">");
	msh->cmd_table[i].filename[*j] = \ 
	//get_io_filename(msh, i, ">", index);
	printf("file:%s\n",msh->cmd_table[i].filename[*j]);
	(*j)++;
	if (*j == 1)
		wordindex = index;
	return (wordindex);
}
*/
void	check_command_table(t_minishell *msh, int i)
{
	int		index;
	int		j;
	int		k;
	char *temp;
	int len;

	index = 0;
	j = 0;
	k = 0;
	len=0;
	count_token(msh, i);
			printf("tk:%d arg:%d\n",msh->cmd_table[index].token_count,msh->cmd_table[index].arg_count);

	while (msh->cmd_table[i].cmd[index])
	{
		temp=ft_strchr(msh->cmd_table[i].cmd[index],'>');
		if (!temp )
		{
			if(msh->cmd_table[i].cmd[index])
			{
			msh->cmd_table[i].exec_table[k] = \
			ft_strdup(msh->cmd_table[i].cmd[index]);
			k++;
			}
		}
		else if(ft_strlen(temp)==1 && temp[0]=='>')
		{
			index++;
			printf("file:%s\n",msh->cmd_table[i].cmd[index]);
			if(ft_strchr(msh->cmd_table[i].cmd[index],'>'))
			{
				len = ft_strlen(msh->cmd_table[i].cmd[index]) -ft_strlen(ft_strchr(msh->cmd_table[i].cmd[index],'>'));
				msh->cmd_table[i].filename[j] = ft_strldup(msh->cmd_table[i].cmd[index],len);
			}
			else
			msh->cmd_table[i].filename[j] = ft_strdup(msh->cmd_table[i].cmd[index]);
			
			printf("file:%s j:%d\n",msh->cmd_table[i].filename[j],j);
			msh->cmd_table[i].tok[j].token = ft_strdup(">");
			j++;
			index++;
			if(index>msh->cmd_table->cmd_count)
				break;
			continue;
		}
		else if(ft_strlen(temp) < ft_strlen(msh->cmd_table[i].cmd[index]) )
		{
			printf("arg b4 >");
			len=ft_strlen(msh->cmd_table[i].cmd[index]) -ft_strlen(temp);
			msh->cmd_table[i].exec_table[k] = \
			ft_strldup(msh->cmd_table[i].cmd[index],len);
			k++;
			//msh->cmd_table[i].arg_count++;
		}
		while(temp)
		{
			 if(ft_strlen(temp)==1 && temp[0]=='>')
			 {
				 index++;
				 if(ft_strchr(msh->cmd_table[i].cmd[index],'>'))
				 {
				len = ft_strlen(msh->cmd_table[i].cmd[index]) -ft_strlen(ft_strchr(msh->cmd_table[i].cmd[index],'>'));
				msh->cmd_table[i].filename[j] = ft_strldup(msh->cmd_table[i].cmd[index],len);
				 }
				 else
					msh->cmd_table[i].filename[j] = ft_strdup(msh->cmd_table[i].cmd[index]);
				 if(index>msh->cmd_table->cmd_count)
				return;
				temp=ft_strchr(msh->cmd_table[i].cmd[index],'>');
				break;
			 }
			msh->cmd_table[i].filename[j] = ft_strdup(check_file_name(temp, ">", index));
			msh->cmd_table[i].tok[j].token = ft_strdup(">");
			printf("file22:%s\n",msh->cmd_table[i].filename[j]);
			j++;
			//tk_handle_redirect_out(msh, i, &j, index);
			if(temp+1)
			temp=ft_strchr(temp+1,  '>');
		}
		/*
		if (!ft_strncmp(msh->cmd_table[i].cmd[index], "$?", 2))
		{
			free(msh->cmd_table[i].cmd[index]);
			msh->cmd_table[i].cmd[index] = ft_itoa(msh->exit_status);
		}
		if (msh->cmd_table[i].cmd[index] && ft_strncmp(msh->cmd_table[i].cmd[index], ">>", 2) == 0)
		{
			msh->cmd_table[i].tok[j].token = ft_strdup(">>");
			msh->cmd_table[i].filename[j] = \
				get_io_filename(msh, i, ">>", index);
			j++;
		}
		else if (msh->cmd_table[i].cmd[index] && ft_strncmp(msh->cmd_table[i].cmd[index], "<<", 2) == 0)
		{
			msh->cmd_table[i].tok[j].token = ft_strdup("<<");
			msh->cmd_table[i].filename[j] = \
			get_io_filename(msh, i, "<<", index);
			j++;
		}
		else if (msh->cmd_table[i].cmd[index] && ft_strchr(msh->cmd_table[i].cmd[index], '<'))
			tk_handle_redirect_in(msh, i, &j, index);
		else if (msh->cmd_table[i].cmd[index] && ft_strchr(msh->cmd_table[i].cmd[index], '>'))
			tk_handle_redirect_out(msh, i, &j, index);
		else if ((j == 0) || (ft_strncmp(msh->cmd_table[i].cmd[index], \
			msh->cmd_table[i].filename[j - 1], \
			ft_strlen(msh->cmd_table[i].cmd[index]))))
		{
			if(msh->cmd_table[i].cmd[index])
			{
			msh->cmd_table[i].exec_table[k] = \
			ft_strdup(msh->cmd_table[i].cmd[index]);
			k++;
			}
		}*/
		index++;
	}
	index=0;
	while(msh->cmd_table[i].exec_table[index])
	{
		printf("exec:%s\n",msh->cmd_table[i].exec_table[index]);
		index++;
	}
	index=0;
	while(msh->cmd_table[i].tok[index].token)
	{
		printf("tok:%s\n",msh->cmd_table[i].tok[index].token);
		index++;
	}
	index=0;
	while(msh->cmd_table[i].filename[index])
	{
		printf("filename:%s\n",msh->cmd_table[i].filename[index]);
		index++;
	}
}
