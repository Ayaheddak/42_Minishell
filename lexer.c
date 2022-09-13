#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

lexer_t	*init_lexer(char *str)
{
	lexer_t *lexer = malloc(sizeof(lexer_t));// allocate memory for this struct
	lexer->contents = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return(lexer);
}
 
void lexer_advance(lexer_t *lexer)
{
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void lexer_skip_whitespace(lexer_t *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
		lexer_advance(lexer);
}

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\t')
		return (1);
	return (0);
}
token_t *lexer_get_next_token(lexer_t *lexer)// 
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
			lexer_skip_whitespace (lexer);
		if (lexer->c == '"')
			return lexer_collect_string(lexer);
		else if (lexer->c == 39)
			return lexer_single_quote(lexer);
		else if (lexer->c == '>')
		{
			return (lexer_advace_with_token(lexer, init_token(TOKEN_OUT, lexer_get_current_char_as_string(lexer))));
			break;
		}
		else if (lexer->c == '<')
		{
			return (lexer_advace_with_token(lexer, init_token(TOKEN_IN, lexer_get_current_char_as_string(lexer))));
			break;
		}
		else if (lexer->c == '|')
		{
			return (lexer_advace_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
			break;
		}
		else
		{
			return lexer_collect_id(lexer);
		}
	}
	return (void*)0;
}
token_t *lexer_single_quote(lexer_t *lexer)
{
	char *value;

	value = malloc(sizeof(char));
	//value[0] = '\0';
	lexer_advance(lexer);
	while (lexer->c != 39)
	{
		char *s = lexer_get_current_char_as_string(lexer);
		strcat(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return init_token(TOKEN_SINGLE_QUOTE, value);
}
token_t *lexer_collect_string(lexer_t *lexer)// TOKEN_DOUBLE_QUOTE,
{
	char *value;

	lexer_advance(lexer);// cuz we're gonna skip the quote
	value = malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->c != '"')
	{
		char *s = lexer_get_current_char_as_string(lexer);
		strcat(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	if(!is_whitespace(lexer->c))
	{
		while (lexer->c != '\0')
		{
			if (lexer->c == 39|| lexer->c == '"')
				lexer_advance(lexer);
			else if (is_whitespace(lexer->c))
				break;
			else 
			{
				char *s = lexer_get_current_char_as_string(lexer);
				strcat(value, s);
				lexer_advance(lexer);
			}
		}
	}
	return init_token(TOKEN_DOUBLE_QUOTE, value);
}

token_t *lexer_collect_id(lexer_t *lexer)//Token string
{
	char *value;

	value = malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\0' && is_whitespace(lexer->c) == 0)
	{
		char *s = lexer_get_current_char_as_string(lexer);
		strcat(value, s);
		lexer_advance(lexer);
	}
	return init_token(TOKEN_STRING, value);
}

token_t *lexer_advace_with_token(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}

char *lexer_get_current_char_as_string(lexer_t *lexer)
{
	char *str = malloc(sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
