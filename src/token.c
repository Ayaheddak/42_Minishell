#include "../includes/minishell.h"

token_t *init_token(int type, char *value)
{
	token_t *token = malloc (sizeof(token_t));
	token->type = type;
	token->value = value;
	return (token);
}