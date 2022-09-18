/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:19:02 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/18 14:59:32 by aheddak          ###   ########.fr       */
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
	char *str = malloc(sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\t')
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
	if (c == 33 || (c >= 35 && c <= 38) || (c >= 40 && c <= 43) || (c >= 45 && c <= 47) ||
		(c >= 58 && c <= 64) || (c >= 91 && c <= 95) || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

int	check_err(char *str)
{
	int i;
	int s_count;
	int d_count;

	i = 0;
	s_count = 0;
	d_count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_count++;
		if (str[i] == 39)
			s_count++;
		i++;
	}
	if(d_count % 2 == 0 && s_count % 2 == 0)
		return (1);
	return (0);
}

token_t	*lexer_get_next_token(lexer_t *lexer)
{
	if (check_err(lexer->contents))
	{
		while (lexer->c != '\0' || lexer->c)
		{
			if (is_whitespace(lexer->c))
				lexer_skip_whitespace (lexer);
			if (lexer->c == '"')
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
	else
		printf("Unclosed quotes\n");
	return (void*)0;
}

// // void	after_quote(lexer_t *lexer ,char *s ,char **value)
// // {
// // 	token_t *token;
// // 	if(!is_whitespace(lexer->c))
// // 	{
// // 		while (lexer->c != '\0')
// // 		{
// // 			if (lexer->c == '"')
// // 			{
// // 				token = lexer_double_quote(lexer);
// // 				*value = ft_strjoin(*value, token->value);
// // 			}
// // 			if (lexer->c == 39)
// // 			{
// // 				token = lexer_single_quote(lexer);
// // 				*value = ft_strjoin(*value, token->value);
// // 			}
// // 			if (is_whitespace(lexer->c) && is_operator(lexer->c))
// // 				break;
// // 			s = lexer_get_current_char_as_string(lexer);
// // 			*value = ft_strjoin(*value, s);
// // 			lexer_advance(lexer);
// // 		}
// // 	}
// // }

// // // void	after_quote(lexer_t *lexer ,char *s ,char **value)
// // // {
// // // 	token_t *token;
// // // 	if(!is_whitespace(lexer->c))
// // // 	{
// // // 		while (lexer->c != '\0')
// // // 		{
// // // 			if (lexer->c == '"')
// // // 			{
// // // 				token = lexer_double_quote(lexer);
// // // 				*value = ft_strjoin(*value, token->value);
// // // 			}
// // // 			if (lexer->c == 39)
// // // 			{
// // // 				token = lexer_single_quote(lexer);
// // // 				*value = ft_strjoin(*value, token->value);
// // // 			}
// // // 			// if (lexer->c == '$')
// // // 			// {
// // // 			// 	token = lexer_expanding(lexer);
// // // 			// 	*value = ft_strjoin(*value, token->value);
// // // 			// }
// // // 			if (is_whitespace(lexer->c) && is_operator(lexer->c))
// // // 				break;
// // // 			s = lexer_get_current_char_as_string(lexer);
// // // 			*value = ft_strjoin(*value, s);
// // // 			lexer_advance(lexer);
// // // 		}
// // // 	}
// // // }

// // int	is_operator_speciaux(char c)
// // {
// // 	if ((c >= 35 && c <= 38) || (c >= 42 && c <= 47) || (c >= 58 && c <= 59) || c == 61 ||
// // 		(c >= 61 && c <= 64) || (c >= 91 && c <= 94) || (c >= 123 && c <= 125) || c == 126)
// // 		return (1);
// // 	return (0);
// // }

// // // token_t *lexer_expanding(lexer_t *lexer)
// // // {
// // // 	char *value;
// // // 	char *s;
	
// // // 	lexer_advance(lexer);
// // // 	value = malloc(sizeof(char));
// // // 	while ((!is_whitespace(lexer->c) && !is_operator_speciaux(lexer->c)) && lexer->c != '\0')
// // // 	{
		
// // // 		s = lexer_get_current_char_as_string(lexer);
// // // 		value = ft_strjoin(value, s);
// // // 		lexer_advance(lexer);
// // // 		if (lexer->c == '"' )
// // // 			break;
// // // 	}
// // // 	value = get_exapanded_test();
// // // 	return init_token(TOKEN_STRING, value);
// // // }
// // // token_t	*lexer_double_quote(lexer_t *lexer)
// // // {
// // // 	char *value;
// // // 	//token_t *token;
// // // 	char *s;

// // // 	lexer_advance(lexer);// cuz we're gonna skip the quote
// // // 	value = malloc(sizeof(char));
// // // 	while (lexer->c != '"'&& lexer->c != '\0')
// // // 	{
// // // 		// if (lexer->c == '$')
// // // 		// {
// // // 		// 	token = lexer_expanding(lexer);
// // // 		// 	value = ft_strjoin(value, token->value);
// // // 		// }
// // // 		if (lexer->c == '"')
// // // 			break;
// // // 		s = lexer_get_current_char_as_string(lexer);
// // // 		value = ft_strjoin(value, s);
// // // 		lexer_advance(lexer);
// // // 	}
// // // 	if (lexer->c == '\0')
// // // 	{
// // // 		printf("Unclosed quotes\n");
// // // 		return (void *)0;
// // // 	}
// // // 	lexer_advance(lexer);
// // // 	after_quote(lexer , s, &value);
// // // 	return init_token(TOKEN_STRING, value);
// // // }

// // token_t	*lexer_double_quote(lexer_t *lexer)
// // {
// // 	char *value;
// // 	//token_t *token;
// // 	char *s;

// // 	lexer_advance(lexer);// cuz we're gonna skip the quote
// // 	value = malloc(sizeof(char));
// // 	while (lexer->c != '"'&& lexer->c != '\0')
// // 	{
// // 		// if (lexer->c == '$')
// // 		// {
// // 		// 	token = token_expanding(lexer);
// // 		// 	value = ft_strjoin(value, token->value);
// // 		// }
// // 		// if (lexer->c == '"')
// // 		// 	break;
// // 		s = lexer_get_current_char_as_string(lexer);
// // 		value = (value, s);
// // 		lexer_advance(lexer);
// // 	}
// // 	if (lexer->c == '\0')
// // 	{
// // 		printf("Unclosed quotes\n");
// // 		return (void *)0;
// // 	}
// // 	lexer_advance(lexer);
// // 	after_quote(lexer , s, &value);
// // 	return init_token(TOKEN_STRING, value);
// // }
// // // token_t	*lexer_single_quote(lexer_t *lexer)
// // // {
// // // 	char *value;
// // // 	char *s;

// // // 	value = malloc(sizeof(char));
// // // 	lexer_advance(lexer);
// // // 	while (lexer->c != 39 && lexer->c != '\0')
// // // 	{
// // // 		s = lexer_get_current_char_as_string(lexer);
// // // 		value = ft_strjoin(value, s);
// // // 		lexer_advance(lexer);
// // // 	}
// // // 	if (lexer->c == '\0')
// // // 	{
// // // 		printf("Unclosed quotes\n");
// // // 		return (void *)0;
// // // 	}
// // // 	lexer_advance(lexer);
// // // 	after_quote(lexer, s, &value);
// // // 	return init_token(TOKEN_STRING, value);
// // // }

// // token_t	*lexer_single_quote(lexer_t *lexer)
// // {
// // 	char *value;
// // 	char *s;

// // 	value = malloc(sizeof(char));
// // 	lexer_advance(lexer);
// // 	while (lexer->c != 39 && lexer->c != '\0')
// // 	{
// // 		s = lexer_get_current_char_as_string(lexer);
// // 		value = ft_strjoin(value, s);
// // 		lexer_advance(lexer);
// // 	}
// // 	if (lexer->c == '\0')
// // 	{
// // 		printf("Unclosed quotes\n");
// // 		return (void *)0;
// // 	}
// // 	lexer_advance(lexer);
// // 	after_quote(lexer, s, &value);
// // 	return init_token(TOKEN_STRING, value);
// // }

// // token_t	*lexer_string(lexer_t *lexer)
// // {
// // 	char *value;
// // 	char *s;
// // 	token_t *token;

// // 	value = malloc(sizeof(char));
// // 	while (lexer->c != '\0' && !is_whitespace(lexer->c))// && !is_operator(lexer->c))
// // 	{
// // 		if (lexer->c == '"')
// // 		{
// // 			token = lexer_double_quote(lexer);
// // 			value = ft_strjoin(value, token->value);
// // 		}
// // 		if (lexer->c == 39)
// // 		{
// // 			token = lexer_single_quote(lexer);
// // 			value = ft_strjoin(value, token->value);
// // 		}
// // 		// if (lexer->c == '$')
// // 		// {
// // 		// 	token = lexer_expanding(lexer);
// // 		// 	value = ft_strjoin(value, token->value);
// // 		// }
// // 		if (is_whitespace(lexer->c))// && is_operator(lexer->c))
// // 			break;
// // 		s = lexer_get_current_char_as_string(lexer);
// // 		value = ft_strjoin(value, s);
// // 		lexer_advance(lexer);
// // 	}
// // 	return init_token(TOKEN_STRING, value);
// // }
// void	after_quote(lexer_t *lexer ,char *s ,char **value)
// {
// 	token_t *token;
// 	if(!is_whitespace(lexer->c))
// 	{
// 		while (lexer->c != '\0')
// 		{
// 			if (lexer->c == '"')
// 			{
// 				token = lexer_double_quote(lexer);
// 				*value = ft_strjoin(*value, token->value);
// 			}
// 			if (lexer->c == 39)
// 			{
// 				token = lexer_single_quote(lexer);
// 				*value = ft_strjoin(*value, token->value);
// 			}
// 			if (is_whitespace(lexer->c) && is_operator(lexer->c))
// 				break;
// 			s = lexer_get_current_char_as_string(lexer);
// 			*value = ft_strjoin(*value, s);
// 			lexer_advance(lexer);
// 		}
// 	}
// }

// // token_t *expanding(lexer_t *lexer)
// // {
// // 	char *value;
// // 	char *s;

// // 	lexer_advance(lexer);// cuz we're gonna skip the quote
// // 	value = malloc(sizeof(char));
// // 	while (!is_whitespace(lexer->c) && lexer->c != '\0')
// // 	{
// // 		s = lexer_get_current_char_as_string(lexer);
// // 		value = ft_strjoin(value, s);
// // 		lexer_advance(lexer);
// // 	}
// // 	return init_token(TOKEN_EXPANDING, value);
	
// // }
// token_t	*lexer_double_quote(lexer_t *lexer)// TOKEN_DOUBLE_QUOTE,
// {
// 	char *value;
// 	char *s;

// 	lexer_advance(lexer);// cuz we're gonna skip the quote
// 	value = malloc(sizeof(char));
// 	while (lexer->c != '"' && lexer->c != '\0')
// 	{
// 		s = lexer_get_current_char_as_string(lexer);
// 		value = ft_strjoin(value, s);
// 		lexer_advance(lexer);
// 	}
// 	if (lexer->c == '\0')
// 	{
// 		printf("Unclosed quotes\n");
// 		return (void *)0;
// 	}
// 	lexer_advance(lexer);
// 	after_quote(lexer , s, &value);
// 	return init_token(TOKEN_STRING, value);
// }

// token_t	*lexer_single_quote(lexer_t *lexer)
// {
// 	char *value;
// 	char *s;

// 	value = malloc(sizeof(char));
// 	lexer_advance(lexer);
// 	while (lexer->c != 39 && lexer->c != '\0')
// 	{
// 		s = lexer_get_current_char_as_string(lexer);
// 		value = ft_strjoin(value, s);
// 		lexer_advance(lexer);
// 	}
// 	if (lexer->c == '\0')
// 	{
// 		printf("Unclosed quotes\n");
// 		return (void *)0;
// 	}
// 	lexer_advance(lexer);
// 	after_quote(lexer, s, &value);
// 	return init_token(TOKEN_STRING, value);
// }
// token_t	*lexer_string(lexer_t *lexer)
// {
// 	char *value;
// 	char *s;
// 	token_t *token;

// 	value = malloc(sizeof(char));
// 	while (lexer->c != '\0' && !is_whitespace(lexer->c) && !is_operator(lexer->c))
// 	{
// 		if (lexer->c == '"')
// 		{
// 			token = lexer_double_quote(lexer);
// 			value = ft_strjoin(value, token->value);
// 		}
// 		if (lexer->c == 39)
// 		{
// 			token = lexer_single_quote(lexer);
// 			value = ft_strjoin(value, token->value);
// 		}
// 		if (is_whitespace(lexer->c) && is_operator(lexer->c))
// 			break;
// 		s = lexer_get_current_char_as_string(lexer);
// 		value = ft_strjoin(value, s);
// 		lexer_advance(lexer);
// 	}
// 	return init_token(TOKEN_STRING, value);
// }