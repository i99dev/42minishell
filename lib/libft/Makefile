NAME = libft.a


SCRS = libft-fun/ft_isdigit.c \
		libft-fun/ft_isascii.c \
		libft-fun/ft_isalpha.c \
		libft-fun/ft_isalnum.c \
		libft-fun/ft_isprint.c \
		libft-fun/ft_strlen.c	\
		libft-fun/ft_memset.c	\
		libft-fun/ft_bzero.c	\
		libft-fun/ft_memcpy.c	\
		libft-fun/ft_toupper.c	\
		libft-fun/ft_tolower.c  \
		libft-fun/ft_strchr.c	\
		libft-fun/ft_memmove.c	\
		libft-fun/ft_strrchr.c	\
		libft-fun/ft_strncmp.c	\
		libft-fun/ft_memchr.c	\
		libft-fun/ft_memcmp.c	\
		libft-fun/ft_strlcpy.c	\
		libft-fun/ft_strlcat.c	\
		libft-fun/ft_strnstr.c	\
		libft-fun/ft_atoi.c	\
		libft-fun/ft_calloc.c	\
		libft-fun/ft_strdup.c	\
		libft-fun/ft_substr.c	\
		libft-fun/ft_strjoin.c	\
		libft-fun/ft_strtrim.c	\
		libft-fun/ft_split.c	\
		libft-fun/ft_itoa.c		\
		libft-fun/ft_strmapi.c	\
		libft-fun/ft_striteri.c	\
		libft-fun/ft_putchar_fd.c	\
		libft-fun/ft_putendl_fd.c	\
		libft-fun/ft_putnbr_fd.c	\
		libft-fun/ft_putstr_fd.c	\
		libft-fun/ft_lstnew.c		\
		libft-fun/ft_lstadd_back.c	\
		libft-fun/ft_lstadd_front.c	\
		libft-fun/ft_lstdelone.c	\
		libft-fun/ft_lstlast.c	\
		libft-fun/ft_lstsize.c	\
		libft-fun/ft_lstclear.c	\
		libft-fun/ft_lstiter.c	\
		libft-fun/ft_lstmap.c


FLAG = -Wall -Wextra -Werror



OBJS_DIR = scr/
OBJS = $(SCRS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_DIR)%.o : %.c libft.h
	@mkdir -p $(OBJS_DIR)/libft-fun
	@echo "Compiling: $<"
	@clang $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED)
	@echo "Libft Done !"

# this rules to work under docker continer for unit test 
so: $(NAME:.a=.so)
$(NAME:.a=.so): $(SCRS)
	$(CC) -shared -o $@ $^
# end 

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: 
	rm -f $(NAME)

re: fclean all