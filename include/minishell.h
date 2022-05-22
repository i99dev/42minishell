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
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
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
	char			**env;
	char			***command_table;
	int				command_count;
	int				*command_type;
	t_token			**token_ls;
	char			***filename_ls;
	int				*token_count;
	char			*user_info;
	char			*line;
	int				**fd_std;
	int				rd;
}	t_minishell;

//color 
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

//action
# define BUILTIN		42
# define LITERAL		43
# define OPERATOR		44
# define REDIRECT		45
# define HER_DOC		46
# define FILE			47
# define PIPE			48
# define AND			49
# define OR				50
# define SEMICOLON		51
# define DOUBLE_AND		52
# define SINGLE			53

# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'\"'

//function
void			prompt_commend(t_minishell *minishell);
void			err_msg(char *msg);
void			define_input_signals(void);
void			pipe_recursive(t_minishell *msh, int i, int in_fd);
int				exec_cd(t_minishell *msh, int i);
int				exec_pwd(void);
void			multi_pipe(t_minishell *msh, int i);
void			execute(t_minishell *msh, int i);
void			init_execute(t_minishell *msh);
void			ft_free_minishell(t_minishell *minishell);
void			free_line(t_minishell *msh);
void			ft_tokenizer(t_minishell *msh);
void			init_command_table(t_minishell *msh);
char			*get_user_info(void);
t_hash_table	*init_table(char **env);
char			*check_file_name(char **str, char *token);

//parser functions
void			start_parser(t_minishell *msh);
void			ft_redirect_in(t_minishell *msh, int index, int token);
void			ft_redirect_out(t_minishell *msh, int index, int token);
void			here_doc(t_minishell *msh, int index);

//tokenizer functions
void			define_type(t_minishell *msh);

//exec functions
char			*get_path(t_minishell *msh, int command_table_index);

#endif