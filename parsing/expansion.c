/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 05:41:04 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/15 05:43:08 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_expanded(char *value)
{
	char	*str;

	str = get_env_value(g_global.env_list, value);
	if (str == NULL)
		return (ft_strdup(""));
	return (str);
}

void	check_err_expanding(lexer_t *lexer, char **value, int tmp)
{
	char	*s;

	while (!is_whitespace(lexer->c) && lexer->c != '\0'
		&& !is_operator_speciaux(lexer->c))
	{
		if (is_whitespace(lexer->c) || lexer->c == '"'
			|| is_operator_speciaux(lexer->c))
		{
			tmp = 1;
			break ;
		}
		s = lexer_get_current_char_as_string(lexer);
		*value = freejoin(*value, s);
		lexer_advance(lexer);
	}
}

t_token	*lexer_expanding(lexer_t *lexer)
{
	char	*value;
	int		tmp;

	value = NULL;
	tmp = 0;
	lexer_advance(lexer);
	if (lexer->c == '?')
	{
		lexer_advance(lexer);
		return (init_token(TOKEN_STRING, ft_itoa(g_global.exitstauts), 0));
	}
	check_err_expanding(lexer, &value, tmp);
	if (tmp == 0 && value == NULL)
	{
		value = ft_strdup("$");
		return (init_token(TOKEN_STRING, value, 0));
	}
	return (init_token(TOKEN_STRING, get_expanded(value), 0));
}

t_token	*expanding_before_heredoc(lexer_t *lexer)
{
	char	*value;
	char	*s;

	value = NULL;
	while (!is_whitespace(lexer->c) && lexer->c != '\0')
	{
		if (is_whitespace(lexer->c) || lexer->c == '"' || lexer->c == 39)
			break ;
		s = lexer_get_current_char_as_string(lexer);
		value = freejoin(value, s);
		lexer_advance(lexer);
	}
	if (ft_strcmp(value, "$") == 0)
	{
		value = "";
		return (init_token(TOKEN_STRING, value, 0));
	}
	return (init_token(TOKEN_STRING, value, 0));
}
