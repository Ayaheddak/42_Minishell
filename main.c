#include <stdio.h>
#include "lexer.h"
int main()
{
	char *inpt;

	inpt = readline("Enter text: ");
	lexer_t *lexer = init_lexer(inpt);
	token_t *token = (void *)0;

	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		printf("token(%d, %s)\n", token->type, token->value);
	}
	return (0);
}