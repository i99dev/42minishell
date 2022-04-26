/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:38:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/22 16:02:12 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>

//mini shell
# include "../lib/libft/libft.h"
# include "./hash.h"
# include "./tokenizer.h"

typedef struct s_minishell
{
	t_hash_table	*env_table;
	char			**command_table;
	t_token			*token_ls;
	char			*user_info;
	char			*line;
}	t_minishell;

//color 
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

//function
void	prompt_commend(t_minishell *minishell);
void	err_msg(char *msg);
void	signal_handler(int sig);
char	*get_user_inf(void);
void	free_exit(char **s1, char **s2, char ***table);
void	execute(t_minishell *msh);
void	ft_free_minishell(t_minishell *minishell);
void	free_line(t_minishell *msh);
void	free_token(t_token *token);

void	ft_tokenizer(char *str, t_minishell *msh);
void	init_command_table(char *input, t_minishell *msh);

#endif