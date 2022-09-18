# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 23:22:45 by aheddak           #+#    #+#              #
#    Updated: 2022/09/18 05:03:06 by aheddak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

UTILS	=	parsing/lexer.c parsing/main.c parsing/token.c parsing/utils.c \
			builtins/change_dir.c builtins/echo.c builtins/env.c builtins/pwd.c builtins/unset.c \
			libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c \
			libft/ft_strncmp.c libft/ft_strtrim.c libft/ft_substr.c

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