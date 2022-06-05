# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 18:46:59 by oal-tena          #+#    #+#              #
#    Updated: 2022/04/22 18:13:11 by oal-tena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Project file
NAME = minishell

MINISHELL_HEADER= include/minishell.h
LIBDIR = lib/libft/
LIBFT = lib/libft/libft.a

SRC= 	src/main.c		\
		src/prompt.c \
		src/tools/exec/execute.c \
		src/tools/exec/pipe.c \
		src/tools/exec/path.c \
		src/tools/exec/built_ins.c \
		src/tools/builtins/ft_echo.c \
		src/tools/builtins/ft_cd.c \
		src/tools/builtins/ft_env.c \
		src/tools/builtins/ft_pwd.c \
		src/tools/builtins/ft_export.c \
		src/tools/builtins/ft_unset.c \
		src/tools/builtins/ft_exit.c \
		src/tools/parser/parser.c \
		src/tools/parser/here_doc.c \
		src/tools/parser/redirect_parser.c \
		src/tools/hash/hash.c \
		src/tools/hash/insert_hash.c\
		src/tools/hash/find_hash.c\
		src/tools/hash/update_hash.c\
		src/tools/hash/remove_hash.c\
		src/tools/hash/print_hash.c\
		src/tools/tokenizer/tokenizer.c \
		src/tools/tokenizer/check_command_table.c \
		src/tools/tokenizer/define_type.c \
		src/tools/tokenizer/quotes.c \
		src/tools/tokenizer/special_case.c \
		src/tools/tokenizer/quotes_remove_quotes.c \
		src/tools/tokenizer/ft_handle_quotes.c \
		src/tools/tokenizer/ft_quotes_str.c \
		src/utils/msg.c \
		src/utils/ft_free.c \
		src/utils/ft_helper.c \
		src/utils/signals.c \
		src/utils/here_doc_signal.c \

CC = gcc -g
CC_FLAG = -Wall -Wextra -Werror -I /usr/local/opt/readline/include

OBJ_DIR = obj/
OBJS = $(SRC:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJS))


$(OBJ_DIR)%.o:%.c $(MINISHELL_HEADER)
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/tools
	@mkdir -p $(OBJ_DIR)/src/tools/parser
	@mkdir -p $(OBJ_DIR)/src/tools/exec
	@mkdir -p $(OBJ_DIR)/src/tools/builtins
	@mkdir -p $(OBJ_DIR)/src/tools/hash
	@mkdir -p $(OBJ_DIR)/src/tools/tokenizer
	@mkdir -p $(OBJ_DIR)/src/utils
	@echo "Compiling $@"
	@$(CC) $(CC_FLAG) -c $< -o $@

$(LIBFT):
	make re -C $(LIBDIR)
	
$(NAME): $(OBJECTS_PREFIXED) $(LIBFT)
	@$(CC) $(CC_FLAG) $(OBJECTS_PREFIXED) $(LIBFT) -o $(NAME) -L /usr/local/opt/readline/lib -lreadline
	@echo "minishell Done !"

leak: #only use to check leak with valgrind
	@echo "leak"
	@make re
	@valgrind --leak-check=full ./$(NAME)

all: $(NAME)
	@make all -C $(LIBDIR)

clean:
	@echo "Cleaning"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBDIR)

fclean: 
	rm -f $(NAME)
	@make fclean -C $(LIBDIR)

re: fclean all