# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smessal <smessal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 14:36:13 by smessal           #+#    #+#              #
#    Updated: 2022/12/02 16:35:39 by smessal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=		srcs/main.c srcs/parsing.c srcs/exec.c utils/utils.c utils/utils_list.c utils/free.c
OBJ =		$(SRC:.c=.o)
CC	=		cc -g
#CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf
NAME	=	pipex
all		=	$(NAME)
$(NAME):	$(OBJ)
				make -C utils/libft
				ar -rcs utils/libft/libft.a
				cp utils/libft/libft.a libft.a
				$(CC) $(OBJ) libft.a -o $(NAME)
clean:
			$(RM) $(OBJ)
			@make clean -sC utils/libft
			
fclean:		clean
			$(RM) $(NAME)
			$(RM) libft.a
			@make fclean -sC utils/libft
			
re:			fclean $(NAME)


.PHONY:		all clean fclean re