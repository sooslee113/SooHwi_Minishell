NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
LIBFT_DIR	=	libft
LIBFT		=	./libft/libft.a
RM			=	rm -rf
SRCS		=	main.c parsing_envp.c parsing_export.c signal.c\
				tokenize_input.c tokenize_split.c util.c error.c\
				pipe_lst.c built_echo.c built_env.c built_export.c\
				built_pwd.c built_unset.c pipe_utils.c lets_free.c execute.c

SRC			=	$(addprefix ./source/,$(SRCS))
OBJ			=	$(SRC:.c=.o)

all			:	$(LIBFT) $(NAME)

$(LIBFT)	:
	@make -s -C $(LIBFT_DIR)

$(NAME)		:	$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft -lreadline

$(OBJ)		:	$(SRC)
	@$(CC) $(CFLAGS) -c $? -I./$(LIBFT_DIR)
	@mv *.o source

clean		:
	@$(RM) source/*.o
	@make -s -C $(LIBFT_DIR) clean

fclean		:	clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re			:	fclean all

.PHONY		:	all clean fclean re
