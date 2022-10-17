/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 04:18:12 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 05:28:50 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*after_quote(lexer_t *lexer, char *s, char **value)
{
	t_token	*token;

	token = NULL;
	lexer_advance(lexer);
	if (!is_whitespace(lexer->c) && lexer->c != '\0')
	{
		while (lexer->c != '\0')
		{
			conditions(lexer, token, value);
			if (lexer->c == '$')
			{
				while (lexer->c == '$')
				{
					token = lexer_expanding(lexer);
					*value = freejoin(*value, token->value);
					free(token);
				}
			}
			s = lexer_get_current_char_as_string(lexer);
			*value = freejoin(*value, s);
			lexer_advance(lexer);
		}
	}
	return (*value);
}

t_token	*lexer_double_quote(lexer_t *lexer)
{
	char	*value;
	char	*s;
	int		tmp;

	value = ft_strdup("");
	tmp = 0;
	if (g_global.last_token && g_global.last_token->e_type == TOKEN_DELIMITER)
		tmp = 1;
	lexer_advance(lexer);
	while (lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$' && tmp == 0)
			while (lexer->c == '$')
				value = freejoin(value, lexer_expanding(lexer)->value);
		if (lexer->c == '"')
			break ;
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '\0')
		return (ft_errer(1));
	if (after_quote(lexer, s, &value) == NULL)
		return ((void *)0);
	return (init_token(TOKEN_STRING, value, 0));
}

t_token	*lexer_single_quote(lexer_t *lexer)
{
	char	*value;
	char	*s;

	value = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != 39 && lexer->c != '\0')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '\0')
		return (ft_errer(1));
	if (after_quote(lexer, s, &value) == NULL)
		return ((void *)0);
	return (init_token(TOKEN_STRING, value, 0));
}
