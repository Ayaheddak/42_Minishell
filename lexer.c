#include "lexer.h"
#include <stdlib.h>
#include <string.h>
lexer_t	*init_lexer(char *contents)
{
	lexer_t *lexer = calloc(1, sizeof(struct lexer_s));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
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
	while (lexer->c == ' ' || lexer->c == 10)
	{
		lexer_advance(lexer);
	}
}
token_t *lexer_get_next_token(lexer_t *lexer)
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace (lexer);
		switch (lexer->c)
		{
			case '=': return (lexer_advace_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)))); break;
			case ';': return (lexer_advace_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)))); break;
			case '(': return (lexer_advace_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)))); break;
			case ')': return (lexer_advace_with_token(lexer, init_token(TOKEN_RPSREN, lexer_get_current_char_as_string(lexer)))); break;
		
		
		}
	}
}
token_t *lexer_collevct_string(lexer_t *lexer)
{

}
token_t *lexer_advace_with_token(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}
char *lexer_get_current_char_as_string(lexer_t *lexer)
{

}