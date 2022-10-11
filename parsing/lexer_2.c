/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:29:40 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/11 00:01:09 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*redirection(lexer_t *lexer, int type1, int type2, char r)
{
	char	*value;
	char	*s;

	value = ft_strdup("");
	value[0] = lexer->c;
	if (lexer->c == r)
	{
		lexer_advance(lexer);
		if (lexer->c == r)
		{
			s = lexer_get_current_char_as_string(lexer);
			value = freejoin(value, s);
			lexer_advance(lexer);
			return (init_token(type2, value));
		}
		else
		{
			lexer->i -= 1;
			return (lexer_advace_with_token(lexer, init_token(type1, &value[0])));
		}
	}
	return ((void *)0);
}

char	*after_quote(lexer_t *lexer , char *s, char **value)//
{
	t_token	*token;

	if (!is_whitespace(lexer->c) && lexer->c != '\0' )
	{
		while (lexer->c != '\0')
		{
			if (lexer->c == '"')
			{
				token = lexer_double_quote(lexer);
				if (token == (void *)0)
					return (NULL);
				*value = freejoin(*value, token->value);
			}
			if (lexer->c == 39)
			{
				token = lexer_single_quote(lexer);
				if (token == (void *)0)
					return (NULL);
				*value = freejoin(*value, token->value);
			}
			if (lexer->c == '$')
			{
				while (lexer->c == '$')
				{
					token = lexer_expanding(lexer);
					*value = freejoin(*value, token->value);
				}
			}
			if (is_whitespace(lexer->c))
				break;
			s = lexer_get_current_char_as_string(lexer);
			*value = freejoin(*value, s);
			lexer_advance(lexer);
		}
	}
	return (*value);
}

t_token	*lexer_double_quote(lexer_t *lexer)//
{
	char	*value;
	char	*s;

	value = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
		{
			while (lexer->c == '$')
				value = freejoin(value, lexer_expanding(lexer)->value);
		}
		if (lexer->c == '"')
			break ;
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '\0')
		return (ft_errer(1));
	lexer_advance(lexer);
	if (after_quote(lexer, s, &value) == NULL)
		return ((void *)0);
	return (init_token(TOKEN_STRING, value));
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
	lexer_advance(lexer);
	if (after_quote(lexer, s, &value) == NULL)
		return ((void *)0);
	return (init_token(TOKEN_STRING, value));
}

t_token	*lexer_string(lexer_t *lexer)//
{
	char	*value;
	char	*s;
	t_token	*token;

	value = ft_strdup("");
	//printf("c---> %c\n", lexer->c);
	while (lexer->c != '\0' && !is_whitespace(lexer->c) && !is_operator(lexer->c))
	{
		if (lexer->c == '$')
		{
			while (lexer->c == '$')
			{
				token = lexer_expanding(lexer);
				value = freejoin(value, token->value);	
			}
		}
		if (lexer->c == '"')
		{
			token = lexer_double_quote(lexer);
			if (token == (void *)0)
				return ((void *)0);
			value = freejoin(value, token->value);
		}
		if (lexer->c == 39)
		{
			token = lexer_single_quote(lexer);
			if (token == (void *)0)
				return ((void *)0);
			value = freejoin(value, token->value);
		}
		if (is_whitespace(lexer->c) || is_operator(lexer->c))
			break ;
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);	
		lexer_advance(lexer);
	}
	//printf("value--> %s\n", value);
	return (init_token(TOKEN_STRING, value));
}

t_token	*lexer_expanding(lexer_t *lexer)
{
	char	*value;
	char	*s;
	int		tmp;

	value = NULL;
	tmp = 0;
	lexer_advance(lexer);
	while (!is_whitespace(lexer->c) && lexer->c != '\0' && !is_operator_speciaux(lexer->c))
	{
		if (is_whitespace(lexer->c) || lexer->c == '"' || is_operator_speciaux(lexer->c))
		{
			tmp = 1;
			break ;
		}
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);
		lexer_advance(lexer);
	}
	if (tmp == 0 && value == NULL)
	{
		value = ft_strdup("$");
		return (init_token(TOKEN_STRING, value));
	}
		//printf("value inside exp --> %s\n", value);
	return (init_token(TOKEN_STRING, get_expanded_test(value)));
}
