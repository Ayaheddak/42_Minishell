#ifndef LEXER_H
#define LEXER_H

typedef struct lexer_s
{
	char			c;
	unsigned int	i;
	char			*contents;
}	lexer_t;

# endif