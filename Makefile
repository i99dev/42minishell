# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 18:46:59 by oal-tena          #+#    #+#              #
#    Updated: 2022/04/19 19:05:36 by oal-tena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Project file
NAME = minishell

MINISHELL_HEADER= include/minishell.h
LIBDIR = lib/libft/
LIBFT = lib/libft/libft.a

SRC= 	/src/main.c		\

CC = gcc -g
CC_FLAG = -Wall -Wextra -Werror

OBJS_DIR = exe/
OBJS = $(SCRS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

OBJ_DIR= obj/
OBJ=$(SRC:.c=.o)
$(OBJ_DIR)%.o:%.c $(MINISHELL_HEADER)
	@mkdir -p $(OBJ_DIR)/src
	@echo "Compiling $@"
	@$(CC) $(CC_FLAG)  -c $< -o $@

$(LIBFT):
	make -C $(LIBDIR)
	
$(NAME): $(LIBFT) $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED) $(LIBFT)
	@echo "mini shell Done !"


all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: 
	rm -f $(NAME)

re: fclean all