/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:19:02 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/16 05:10:22 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

lexer_t	*init_lexer(char *str)
{
	lexer_t	*lexer;

	if (!str)
		return (NULL);
	lexer = malloc(sizeof(lexer_t));
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
	leaks_removal(&g_global.g, str);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
