#ifndef TOKEN_H
#define TOKEN_H
typedef struct token_s
{
	enum
	{
		// TOKEN_ID,//TOKEN_SINGLE_QUOTE
		// TOKEN_EQUALS,//TOKEN_IN
		// TOKEN_STRING,//TOKEN_OUT
		// TOKEN_SEMI,//semicolon
		// TOKEN_LPAREN,//TOKEN_HEARD
		// TOKEN_RPSREN,//TOKEN_DOUBLE_QUOTE
		//TOKEN_STRING,
		TOKEN_DOUBLE_QUOTE,
		TOKEN_SINGLE_QUOTE,
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_IN,
		TOKEN_OUT,
	} type;

	char *value;

}	token_t;

token_t *init_token(int type, char *value);

# endif