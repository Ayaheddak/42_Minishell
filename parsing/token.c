/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:49 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 05:30:34 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(int type, char *value, int split)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	leaks_removal(&g_global.g, token);
	token->e_type = type;
	token->value = value;
	token->split = split;
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (is_whitespace(lexer->c))
			lexer_skip_whitespace (lexer);
		else if (lexer->c == '"')
			return (lexer_double_quote(lexer));
		else if (lexer->c == 39)
			return (lexer_single_quote(lexer));
		else if (lexer->c == '<')
			return (redirection(lexer, TOKEN_IN, TOKEN_DELIMITER, '<'));
		else if (lexer->c == '>')
			return (redirection(lexer, TOKEN_OUT, TOKEN_APPEND, '>'));
		else if (lexer->c == '|')
		{
			return (lexer_advace_with_token(lexer, init_token(TOKEN_PIPE,
						lexer_get_current_char_as_string(lexer), 0)));
			break ;
		}
		else
			return (lexer_string(lexer));
	}
	return ((void *)0);
}

t_token	*tokenizer(t_lexer *lexer)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	g_global.last_token = 0;
	token = lexer_get_next_token(lexer);
	while (token != (void *)0)
	{
		addback(&head, token->value, &token->e_type, token->split);
		g_global.last_token = token;
		token = lexer_get_next_token(lexer);
	}
	free(g_global.last_token);
	free(token);
	return (head);
}

void	free_tokenizer(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free (tmp);
	}
	free (token);
}
