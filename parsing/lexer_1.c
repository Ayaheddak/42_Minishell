/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:19:02 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/10 23:04:41 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//function for replace expanded

char	*get_expanded_test(char *value)
{
	char *str;

	str = get_env_value(g_global.env_list, value);
	if (str == NULL)
		return (ft_strdup(""));
	return (str);
}

/*
char	*get_exapanded_test(void)
{
	return (strdup("[EXPANDED VALUE]"));
}
*/ 

lexer_t	*init_lexer(char *str)
{
	lexer_t	*lexer;

	lexer = malloc(sizeof(lexer_t));//
	lexer->contents = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return (lexer);
}

void	lexer_advance(lexer_t *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(lexer_t *lexer)
{
	while (is_whitespace(lexer->c))
		lexer_advance(lexer);
}

t_token	*lexer_advace_with_token(lexer_t *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(lexer_t *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
