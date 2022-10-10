# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 23:22:45 by aheddak           #+#    #+#              #
#    Updated: 2022/10/10 13:41:38 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

UTILS	=	parsing/lexer_1.c parsing/main.c parsing/token.c parsing/utils_list.c parsing/lexer_2.c parsing/parser.c \
			libft/ft_isalpha.c libft/ft_lstadd_back_bonus.c libft/ft_memchr.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_strlcpy.c libft/ft_strrchr.c \
			libft/ft_atoi.c libft/ft_isascii.c libft/ft_memcmp.c libft/ft_putendl_fd.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strtrim.c \
			libft/ft_bzero.c libft/ft_isdigit.c libft/ft_memcpy.c libft/ft_putnbr_fd.c libft/ft_striteri.c libft/ft_strmapi.c libft/ft_substr.c \
			libft/ft_calloc.c libft/ft_isprint.c libft/ft_lstnew_bonus.c libft/ft_memmove.c libft/ft_putstr_fd.c libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_tolower.c \
			libft/ft_isalnum.c libft/ft_itoa.c libft/ft_lstsize_bonus.c libft/ft_memset.c libft/ft_split.c libft/ft_strlcat.c libft/ft_strnstr.c libft/ft_toupper.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/lexer_utils.c\
			env_variables/env_list.c env_variables/env_list_utils.c parsing/parsing_utils.c\
			execution/execute.c execution/start_exec.c execution/close.c execution/io_streams.c \
			builtins/echo.c builtins/call_builtins.c builtins/change_dir.c builtins/env.c builtins/pwd.c builtins/unset.c builtins/export.c

FLAGS	=	 -Wall -Wextra -Werror #-fsanitize=address -g3


# OBJCT	=	${UTILS:.c=.o}

RM		=	rm -f

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(UTILS)	
	@$(CC) $(FLAGS) $(UTILS) -o $(NAME) -lreadline -g3

clean :
	@${RM} $(OBJCT)

fclean :	clean
	@${RM} ${NAME}
 
re : fclean all
