#ifndef TOKEN_H
#define TOKEN_H
typedef struct token_s
{
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_IN,
		TOKEN_OUT,
		TOKEN_JSP,
		TOKEN_EXPANDING,

	} type;

	char *value;

}	token_t;

token_t *init_token(int type, char *value);

# endif