# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 23:22:45 by aheddak           #+#    #+#              #
#    Updated: 2022/09/17 15:16:08 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

UTILS	=	src/lexer.c src/main.c src/token.c src/utils.c libft/*.c builtins/*.c

FLAGS	=	-Wall -Wextra -Werror

OBJCT	=	${UTILS:.c=.o}

RM		=	rm -f

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJCT)	
	$(CC) $(FLAGS) $(UTILS) -o $(NAME) -lreadline

clean :
	${RM} $(OBJCT)

fclean :	clean
	${RM} ${NAME}
 
re : fclean all