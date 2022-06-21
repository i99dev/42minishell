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
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>

//mini shell
# include "../lib/libft/libft.h"
# include "./hash.h"
# include "./tokenizer.h"

typedef struct s_cmdt
{
	char			**cmd;
	char			**exec_table;
	t_token			**tok;
	char			**filename;
	int				command_type;
	int				cmd_count;
	int				token_count;
	int				arg_count;
}	t_cmdt;
/*
line = "grep src > file"
msh->cmd_table[0]->cmd = {"grep", "src", ">", "file"}
msh->cmd_table[0]->tok = {["grep", -1 ],["src", -1],["RDOUT", '>']}
msh->cmd_table[0]->exec = {"grep", "src"}
msh->cmd_table[0]->filename = {"file"}
msh->token_count = 1
msh->command_type = BIN or BUILTIN
*/

typedef struct s_minishell
{
	t_hash_table	*env_table;
	char			**env;
	t_cmdt			**cmd_table;
	char			**quotes;
	int				quote_count;
	int				command_count;
	char			*user_info;
	char			*line;
	int				*fd_std;
	int				q_pos;
	int				rd;
	int				last_fd;
	int				exit_status;
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
void			define_input_signals(t_minishell *msh);
void			define_exec_signals(t_minishell *msh);
void			interrupt_here_document(int signal);
void			pipe_recursive(t_minishell *msh, int i, int in_fd);
void			multi_pipe(t_minishell *msh, int i);
void			execute(t_minishell *msh, int i);
void			execute_builtin(t_minishell *msh, int i);
void			init_execute(t_minishell *msh);
void			ft_free_minishell(t_minishell *minishell);
void			free_line(t_minishell *msh);
bool			ft_tokenizer(t_minishell *msh);
void			init_command_table(t_minishell *msh);
char			*get_user_info(t_minishell *msh);
t_hash_table	*init_table(char **env);
char			*check_file_name(char **str, char *token, int index);
char			*ft_strldup(const char *s1, int i);
//function hash
void			update_hash(t_minishell *msh, char *key, char *value);
void			remove_hash(t_minishell *msh, char *key);

//parser functions
void			start_parser(t_minishell *msh);
void			ft_redirect(t_minishell *msh, int i);
void			ft_redirect_in(t_minishell *msh, int index, int token);
void			ft_redirect_out(t_minishell *msh, int index, int token);
void			here_doc(t_minishell *msh, int i, int index);
void			ft_redirect_append(t_minishell *msh, int index, int token);
//function for here_doc
void			doc_line_doc(t_minishell *msh, int temp_fd, char *eof);
char			*doc_get_heredoc(char *str);
void			doc_tmp_file(void);

//tokenizer functions
void			define_type(t_minishell *msh);
void			ft_check_quotes(t_minishell *msh);
void			ft_handle_quotes(t_minishell *msh);
bool			check_command_table(t_minishell *msh, int i);
void			ft_special_case(t_minishell *msh);
bool			is_token(char *str);
bool	special_char_with_dollar(char *word);
int				q_remove_quotes(t_minishell *msh, int start, \
				int end, int q_index);
int				q_count_quotes(t_minishell *msh);
char			*ft_strinsert(char *str, char *in, char *key);
char			*expand_parameters(t_minishell *msh, char *str);
char			*expand_cmd(t_minishell *msh, char *str);
char				*find_hash(t_minishell *msh, t_hash_table *env_table, char *key);
bool	q_handle_all(t_minishell *msh, int i, int *j, int *k);
//builtin functions
void			ft_echo(t_minishell *msh, int i);
void			ft_env(t_minishell *msh, int i);
void			ft_export(t_minishell *msh, int i);
void			ex_export_env(t_minishell *msh, int i);
void			ft_pwd(t_minishell *msh);
void			ft_unset(t_minishell *msh, int i);
void			ft_cd(t_minishell *msh, int i);
void			ft_exit(t_minishell *msh, int i);


//exec functions
char			*get_path(t_minishell *msh, int command_table_index);

//function for utils
void			error_message(t_minishell *msh, char *error_message, \
int status);
void			free_loop(t_minishell *msh);
void			ft_free_hash(t_hash_table *table);

#endif