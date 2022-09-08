#ifndef TOKEN_H
#define TOKEN_H
typedef struct token_s
{
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPSREN,
	} type;
	char *value;
}	token_t;

token_t *init_token(int type, char *value);

# endif