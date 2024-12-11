NAME = export.out

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SUBDIR = libft

SRCS_MUST = ft_export.c \
	    parsing_envp.c \
		parsing_export.c \
		parsing_env.c \
	    ./libft/ft_strnstr.c \
	    ./libft/ft_strjoin.c \
	    ./libft/ft_strlen.c \
	    ./libft/ft_substr.c \
	    ./libft/ft_strdup.c \
	    ./libft/ft_split.c \
		./libft/ft_isalpha.c \
		./libft/ft_isalnum.c 


		
SRCS = $(SRCS_MUST)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c 
	@make re -C ./libft
	$(CC) $(CFLAGS) -c  $< -o  $@

clean:
	@make clean -C ./libft
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all