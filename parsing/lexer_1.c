/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:19:02 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/22 02:09:48 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exapanded_test()//function for replace expanded
{
	return (strdup("[EXPANDED VALUE]"));
	//return strdup("");
}

lexer_t	*init_lexer(char *str)
{
	lexer_t *lexer = malloc(sizeof(lexer_t));
	lexer->contents = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return(lexer);
}
 
void	lexer_advance(lexer_t *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(lexer_t *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
		lexer_advance(lexer);
}

token_t	*lexer_advace_with_token(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(lexer_t *lexer)
{
	char *str = malloc(sizeof(char) * 2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return 1;
	return 0;
}

int	is_operator_speciaux(char c)
{
	if ((c >=35 && c <= 39) || (c >= 42 && c <= 47) || (c >= 58 && c <= 59) || c == 61 ||
		(c >= 61 && c <= 64) || (c >= 91 && c <= 94) || (c >= 123 && c <= 125) || c == 126)
		return (1);
	return (0);
}

int check_err(char *str)
{
	int i;
	int count_dq;
	int count_sq;

	i = 0;
	count_dq = 0;
	count_sq = 0;
	while (str[i])
	{
		if (str[0] == '|' || (str[i] == '|' && str[i + 1] == '|') || (str[i + 1] == '\0' && str[i + 1] == '|'))
			return (printf("Error : Unexpected token \n"));
		if (str[0] == '>' || str[0] == '<')
			return (printf("Error : invalid redirection \n"));
		if ((str[i + 1] == '\0' && str[i] == '>') || (str[i + 1] == '\0' && str[i] == '<'))
			return (printf("Error : Unexpected token newlin \n"));
		if (str[i] == '"' && str[i] != '\0')
		{
			count_dq++;
			i++;
			while(str[i] != '"' && str[i] != '\0' )
				i++;
			if (str[i] == '"')
				count_dq++;
		}
		if (str[i] == 39 && str[i] != '\0')
		{
			count_sq++;
			i++;
			while(str[i] != 39 && str[i] != '\0')
				i++;
			if (str[i] == 39)
				count_sq++;
		}
		i++;
	}
	if (count_dq % 2 == 0 && count_sq % 2 == 0)
		return (1);
	else
		return (printf("Error : Unclosed quotes\n"));
		
}

token_t	*lexer_get_next_token(lexer_t *lexer)
{
	if (check_err(lexer->contents) == 1)
	{
		while (lexer->c != '\0' || lexer->c)
		{
			if (is_whitespace(lexer->c))
				lexer_skip_whitespace (lexer);
			else if (lexer->c == '"')
				return lexer_double_quote(lexer);
			else if (lexer->c == 39)
				return lexer_single_quote(lexer);
			else if (lexer->c == '<')
				return (redirection(lexer, TOKEN_IN, TOKEN_DELIMITER, '<'));
			else if (lexer->c == '>')
				return (redirection(lexer, TOKEN_OUT,TOKEN_APPEND, '>'));
			else if (lexer->c == '|')
			{
				return (lexer_advace_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
				break;
			}
			else
				return lexer_string(lexer);
		}
	}
	return (void*)0;
}
