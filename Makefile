# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 20:26:36 by donghwi2          #+#    #+#              #
#    Updated: 2024/11/26 01:52:10 by donghwi2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
LIBFT_DIR	=	libft
LIBFT		=	./libft/libft.a
RM			=	rm -rf
SRCS		=	main.c parsing_envp.c parsing_export.c signal.c\
				tokenize_input.c tokenize_split.c util.c error.c
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