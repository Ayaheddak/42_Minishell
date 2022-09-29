# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 23:22:45 by aheddak           #+#    #+#              #
#    Updated: 2022/09/29 22:01:43 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

UTILS	=	parsing/lexer_1.c parsing/main.c parsing/token.c parsing/utils_list.c parsing/lexer_2.c parsing/parser.c \
			builtins/change_dir.c builtins/echo.c builtins/env.c builtins/pwd.c builtins/unset.c builtins/exit.c \
			libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c \
			libft/ft_strncmp.c libft/ft_strtrim.c libft/ft_substr.c builtins/export.c builtins/call_builtins.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
			execution/redirections.c execution/execute.c execution/start_exec.c execution/close.c execution/io_streams.c

FLAGS	=	-Wall -Wextra -Werror

OBJCT	=	${UTILS:.c=.o}

RM		=	rm -f

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJCT)	
	@$(CC) $(FLAGS) $(UTILS) -o $(NAME) -lreadline -g #-fsanitize=address

clean :
	@${RM} $(OBJCT)

fclean :	clean
	@${RM} ${NAME}
 
re : fclean all