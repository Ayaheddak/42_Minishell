#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_IN,//<
		TOKEN_OUT,//>
		TOKEN_APPEND,
		TOKEN_DELIMITER,
	}	type;
	char *value;
	struct s_token *next;
}	t_token;
# endif