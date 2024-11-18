# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 20:26:36 by donghwi2          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/11/18 21:39:33 by donghwi2         ###   ########.fr        #
=======
#    Updated: 2024/11/18 19:26:33 by sooslee          ###   ########.fr        #
>>>>>>> ca12df94f4f509be8b532268d4f3c8d379c62a47
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = libft
LIBFT = ./libft/libft.a
RM = rm -rf
<<<<<<< HEAD
SRCS = main.c parsing_env.c parsing_envp.c parsing_export.c signal.c util.c
=======
SRCS = main.c parsing_envp.c signal.c
>>>>>>> ca12df94f4f509be8b532268d4f3c8d379c62a47
SRC	= $(addprefix ./source/,$(SRCS))
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft -lreadline

$(OBJ): $(SRC)
	@$(CC) $(CFLAGS) -c $? -I./$(LIBFT_DIR)
	@mv *.o source

clean:
	@$(RM) source/*.o
	@make -s -C $(LIBFT_DIR) clean

fclean:	clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY: all clean fclean re