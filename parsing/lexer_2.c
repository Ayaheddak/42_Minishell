/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:29:40 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/19 17:03:25 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

token_t *redirection(lexer_t *lexer, int type1, int type2, char r)
{
	char *value;
	char *s;
	
	value = malloc(sizeof(char));
	value[0] = lexer->c;
	if (lexer->c == r)
	{
		lexer_advance(lexer);
		if (lexer->c == r)
		{
			s = lexer_get_current_char_as_string(lexer);
			value = ft_strjoin(value, s);
			lexer_advance(lexer);
			return init_token(type2, value);
		}
		else
		{
			lexer->i  -=1;
			return lexer_advace_with_token(lexer, init_token(type1,&value[0]));
		}
	}
	return (void *)0;
}

void	after_quote(lexer_t *lexer ,char *s ,char **value)
{
	token_t *token;
	if(!is_whitespace(lexer->c))
	{
		while (lexer->c != '\0')
		{
			if (lexer->c == '"')
			{
				token = lexer_double_quote(lexer);
				*value =ft_strjoin(*value, token->value);
			}
			if (lexer->c == 39)
			{
				token = lexer_single_quote(lexer);
				*value = ft_strjoin(*value, token->value);
			}
			if (lexer->c == '$')
			{
				while(lexer->c == '$')
				{
					token = lexer_expanding(lexer);
					*value = ft_strjoin(*value, token->value);
				}
			}
			if (is_whitespace(lexer->c))
				break;
			s = lexer_get_current_char_as_string(lexer);
			*value = ft_strjoin(*value, s);
			lexer_advance(lexer);
		}
	}
}

token_t	*lexer_double_quote(lexer_t *lexer)
{
	char *value;
	token_t *token;
	char *s;

	value = malloc(sizeof(char));
	lexer_advance(lexer);// cuz we're gonna skip the quote
	while (lexer->c != '"'&& lexer->c != '\0')
	{
		if (lexer->c == '$')
		{
			while (lexer->c == '$')
			{
				token = lexer_expanding(lexer);
				value = ft_strjoin(value, token->value);
			}
		}
		if (lexer->c == '"')
			break;
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '\0')
	{
		printf("Unclosed quotes\n");
		return (void *)0;
	}
	lexer_advance(lexer);
	after_quote(lexer , s, &value);
	return init_token(TOKEN_STRING, value);
}

token_t	*lexer_single_quote(lexer_t *lexer)
{
	char *value;
	char *s;

	value = malloc(sizeof(char));
	lexer_advance(lexer);
	while (lexer->c != 39 && lexer->c != '\0')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '\0')
	{
		printf("Unclosed quotes\n");
		return (void *)0;
	}
	lexer_advance(lexer);
	after_quote(lexer, s, &value);
	return init_token(TOKEN_STRING, value);
}

token_t	*lexer_string(lexer_t *lexer)
{
	char *value;
	char *s;
	token_t *token;

	value = NULL;
	while (lexer->c != '\0' && !is_whitespace(lexer->c) && !is_operator(lexer->c))
	{
		if (lexer->c == '"')
		{
			token = lexer_double_quote(lexer);
			value = ft_strjoin(value, token->value);
		}
		if (lexer->c == 39)
		{
			token = lexer_single_quote(lexer);
			value = ft_strjoin(value, token->value);
		}
		if (lexer->c == '$')
		{
			while (lexer->c == '$')
			{
				token = lexer_expanding(lexer);
				value = ft_strjoin(value, token->value);
			}
		}
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoin(value, s);
		if (is_whitespace(lexer->c) || is_operator(lexer->c))
			break;
		lexer_advance(lexer);
	}
	return init_token(TOKEN_STRING, value);
}

token_t *lexer_expanding(lexer_t *lexer)
{
	char *value;
	char *s;
	
	lexer_advance(lexer);// cuz we're gonna skip $
	value = malloc(sizeof(char));
	while (!is_whitespace(lexer->c) && lexer->c != '\0' && !is_operator_speciaux(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if (is_whitespace(lexer->c) || lexer->c == '"' || is_operator_speciaux(lexer->c))
			break;
	}
	return init_token(TOKEN_EXPANDING, get_exapanded_test());
}