NAME = ft_env.out

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT_SRCS = ft_strnstr.c \
             ft_strjoin.c \
             ft_strlen.c \
             ft_substr.c \
             ft_strdup.c \
             ft_split.c \
             ft_isalpha.c \
             ft_isalnum.c

LIBFT_OBJS = $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS:.c=.o))

SRCS = ft_env.c \


OBJS = $(SRCS:.c=.o) $(LIBFT_OBJS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/%.o : $(LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBFT_OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
