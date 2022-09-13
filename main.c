#include <stdio.h>
#include "lexer.h"
int main()
{
	lexer_t *lexer = init_lexer("   \'\'\"he\'ll\'o\"\'\'   ");
	token_t *token = (void *)0;

	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		printf("token(%d, %s)\n", token->type, token->value);
	}
	return (0);
}