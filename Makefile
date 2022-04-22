# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 18:46:59 by oal-tena          #+#    #+#              #
#    Updated: 2022/04/22 13:04:23 by oal-tena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Project file
NAME = minishell

MINISHELL_HEADER= include/minishell.h
LIBDIR = lib/libft/
LIBFT = lib/libft/libft.a

SRC= 	src/main.c		\
		src/tools/prompt.c \
		src/utils/msg.c \
		src/tools/parser.c \
		src/tools/execute.c \

CC = gcc -g
CC_FLAG = -Wall -Wextra -Werror

OBJ_DIR = obj/
OBJS = $(SRC:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJS))

$(OBJ_DIR)%.o:%.c $(MINISHELL_HEADER)
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/tools
	@mkdir -p $(OBJ_DIR)/src/utils
	@echo "Compiling $@"
	@$(CC) $(CC_FLAG) -c $< -o $@

$(LIBFT):
	make -C $(LIBDIR)
	
$(NAME): $(OBJECTS_PREFIXED) $(LIBFT)
	@$(CC) $(OBJECTS_PREFIXED) $(LIBFT) -o $(NAME) -lreadline
	@echo "minishell Done !"

leak: #only use to check leak with valgrind
	@echo "leak"
	@valgrind --leak-check=full ./$(NAME)

all: $(NAME)

clean:
	@echo "Cleaning"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

fclean: 
	rm -f $(NAME)

re: fclean all