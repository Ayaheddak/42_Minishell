/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:29:40 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 05:33:36 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*redirection(t_lexer *lexer, int type1, int type2, char r)
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

void	conditions(t_lexer *lexer, t_token *token, char **value)
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

int	check_redir(void)
{
	if (g_global.last_token && is_redir(g_global.last_token) == 5)
		return (1);
	else if (g_global.last_token && is_redir(g_global.last_token) > 0)
		return (2);
	else
		return (0);
}

void	lexer_string_conds(t_lexer *lexer, t_token *token, char **value, int *a)
{
	int	tmp;

	tmp = 0;
	if (check_redir() == 1)
		tmp = 1;
	if (check_redir() == 2)
		tmp = 2;
	if (lexer->c == '$' && (tmp == 0 || tmp == 2))
	{
		while (lexer->c == '$')
		{
			token = lexer_expanding(lexer);
			*value = freejoin(*value, token->value);
		}
		*a = needs_splitting(token->value);
	}
	if (lexer->c == '$' && tmp == 1)
	{
		while (lexer->c == '$')
		{
			token = expanding_before_heredoc(lexer);
			*value = freejoin(*value, token->value);
		}
	}
}

t_token	*lexer_string(t_lexer *lexer)
{
	t_token	*token;
	char	*value;
	char	*s;
	int		a;

	a = 0;
	token = NULL;
	value = ft_strdup("");
	while (lexer->c != '\0' && !is_whitespace(lexer->c)
		&& !is_operator(lexer->c))
	{
		lexer_string_conds(lexer, token, &value, &a);
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
