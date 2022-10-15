/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:29:40 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/15 05:46:22 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*redirection(lexer_t *lexer, int type1, int type2, char r)
{
	char	*value;
	char	*s;
	char	now;

	now = lexer->c;
	value = conv_char(now);
	if (lexer->c == r)
	{
		lexer_advance(lexer);
		if (lexer->c == r)
		{
			s = lexer_get_current_char_as_string(lexer);
			value = freejoin(value, s);
			lexer_advance(lexer);
			return (init_token(type2, value, 0));
		}
		else
		{
			lexer->i -= 1;
			return (lexer_advace_with_token(lexer,
					init_token(type1, &value[0], 0)));
		}
	}
	return ((void *)0);
}

void	conditions(lexer_t *lexer, t_token *token, char **value)
{
	if (lexer->c == '"')
	{
		token = lexer_double_quote(lexer);
		if (token == (void *)0)
			return ;
		*value = freejoin(*value, token->value);
		free(token);
	}
	if (lexer->c == 39)
	{
		token = lexer_single_quote(lexer);
		if (token == (void *)0)
			return ;
		*value = freejoin(*value, token->value);
		free(token);
	}
}

char	*after_quote(lexer_t *lexer, char *s, char **value)
{
	t_token	*token;

	token = NULL;
	lexer_advance(lexer);
	if (!is_whitespace(lexer->c) && lexer->c != '\0' )
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
			if (is_whitespace(lexer->c))
				break ;
			s = lexer_get_current_char_as_string(lexer);
			*value = freejoin(*value, s);
			lexer_advance(lexer);
		}
	}
	return (*value);
}

int	check_redir(void)
{
	if (g_global.last_token && is_redir(g_global.last_token) == 5)
		return (1);
	else if (g_global.last_token && is_redir(g_global.last_token) > 0)
		return (2);
	else
		return (0);
}

t_token	*lexer_double_quote(lexer_t *lexer)
{
	char	*value;
	char	*s;
	int		tmp;

	value = ft_strdup("");
	tmp = 0;
	if (g_global.last_token && g_global.last_token->type == TOKEN_DELIMITER)
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

t_token	*lexer_string(lexer_t *lexer)
{
	t_token	*token;
	char	*value;
	char	*s;
	int		a;
	int		tmp;

	a = 0;
	tmp = 0;
	value = ft_strdup("");
	// if (g_global.last_token && is_redir(g_global.last_token) == TOKEN_DELIMITER)
	// 	tmp = 1;;
	if (check_redir() == 1)//
		tmp = 1;
	// if (check_redir()== 2)
	// 	tmp = 2;
	while (lexer->c != '\0' && !is_whitespace(lexer->c) && !is_operator(lexer->c))
	{
		if (lexer->c == '$' && tmp == 0)
		{
			while (lexer->c == '$')
			{
				token = lexer_expanding(lexer);
				value = freejoin(value, token->value);
			}
			a = needs_splitting(token->value);
		}
		if (lexer->c == '$' && tmp == 1)
		{
			while (lexer->c == '$')
			{
				token = expanding_before_heredoc(lexer);
				value = freejoin(value, token->value);
			}
		}
		// else if (lexer->c == '$' && tmp == 2)
		// {
		// 	while (lexer->c == '$')
		// 	{
		// 		token = lexer_expanding(lexer);
		// 		value = freejoin(value, token->value);
		// 	}
		// 	a = needs_splitting(token->value);
		// 	if (a == 1)
		// 		value = strdup("");
		// }
		conditions(lexer, token, &value);
		if (is_whitespace(lexer->c) || is_operator(lexer->c))
			break ;
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_STRING, value, a));
}
