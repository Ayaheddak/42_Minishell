/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:19:02 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 03:48:28 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	if (!str)
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	lexer->contents = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (is_whitespace(lexer->c))
		lexer_advance(lexer);
}

t_token	*lexer_advace_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	leaks_removal(&g_global.g, str);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
