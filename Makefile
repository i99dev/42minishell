# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 18:46:59 by oal-tena          #+#    #+#              #
#    Updated: 2022/04/21 11:22:14 by oal-tena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Project file
NAME = minishell

MINISHELL_HEADER= include/minishell.h
LIBDIR = lib/libft/
LIBFT = lib/libft/libft.a

SRC= 	src/main.c		\
		src/tools/prompt.c \

CC = gcc -g
CC_FLAG = -Wall -Wextra -Werror -lreadline 

OBJ_DIR = obj/
OBJS = $(SRC:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJS))

$(OBJ_DIR)%.o:%.c $(MINISHELL_HEADER)
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/tools
	@echo "Compiling $@"
	@$(CC) -c $< -o $@

$(LIBFT):
	make -C $(LIBDIR)
	
$(NAME): $(OBJECTS_PREFIXED) $(LIBFT)
	@$(CC) $(CC_FLAG) $(OBJECTS_PREFIXED) $(LIBFT) -o $(NAME)
	@echo "minishell Done !"


all: $(NAME)

clean:
	@echo "Cleaning"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

fclean: 
	rm -f $(NAME)

re: fclean all