#ifndef LEXER_H
#define LEXER_H
#include "token.h"
typedef struct lexer_s
{
	char			c;
	unsigned int	i;
	char			*contents;//the source code that we're gonna parce
}	lexer_t;

lexer_t	*init_lexer(char *contents);

void lexer_advance(lexer_t *lexer);//going to move our pointer to the next character in the content

void lexer_skip_whitespace(lexer_t *lexer);

token_t *lexer_get_next_token(lexer_t *lexer);// func to get next token in the contents

token_t *lexer_collect_string(lexer_t *lexer);

token_t *lexer_collect_id(lexer_t *lexer);

token_t *lexer_advace_with_token(lexer_t *lexer, token_t *token);
token_t *lexer_single_quote(lexer_t *lexer);
char *lexer_get_current_char_as_string(lexer_t *lexer); //this func is going to return this "char c" but as a string (whhhhhhhy !!!!!!)

# endif