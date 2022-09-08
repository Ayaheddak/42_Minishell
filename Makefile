# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 23:22:45 by aheddak           #+#    #+#              #
#    Updated: 2022/09/07 23:23:16 by aheddak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

UTILS	=	lexer.c

FLAGS	=	-Wall -Wextra -Werror

OBJCT	=	${UTILS:.c=.o}

RM		=	rm -f

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJCT)	
	$(CC) $(FLAGS) $(UTILS) -o $(NAME)

clean :
	${RM} $(OBJCT)

fclean :	clean
	${RM} ${NAME}

re : fclean all