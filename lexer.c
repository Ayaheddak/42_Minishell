#include "lexer.h"

lexer_t	*init_lexer(char *str)
{
	lexer_t *lexer = malloc(sizeof(lexer_t));// allocate memory for this struct
	lexer->contents = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
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
	while (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
		lexer_advance(lexer);
}

token_t *lexer_advace_with_token(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}

char *lexer_get_current_char_as_string(lexer_t *lexer)
{
	char *str = malloc(sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\t')
		return (1);
	return (0);
}

int check_err(char *str)
{
	int i;
	int s_count;
	int d_count;

	i = 0;
	s_count = 0;
	d_count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_count++;
		if (str[i] == 39)
			s_count++;
		i++;
	}
	if(d_count % 2 == 0 && s_count % 2 == 0)
		return (1);
	return (0);
}
token_t *lexer_get_next_token(lexer_t *lexer)
{
	if (check_err(lexer->contents))
	{
		while (lexer->c != '\0')
		{
			if (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
				lexer_skip_whitespace (lexer);
			else if (lexer->c == '"')
				{
					//printf("hello from dq \n");
					return lexer_double_quote(lexer);
				}
			else if (lexer->c == 39)
			{
				//printf("hello from sq \n");
				return lexer_single_quote(lexer);
			}
			else if (lexer->c == '<')
			{
				return (lexer_advace_with_token(lexer, init_token(TOKEN_OUT, lexer_get_current_char_as_string(lexer))));
				break;
			}
			else if (lexer->c == '>')
			{
				return (lexer_advace_with_token(lexer, init_token(TOKEN_IN, lexer_get_current_char_as_string(lexer))));
				break;
			}
			else if (lexer->c == '|')
			{
				return (lexer_advace_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
				break;
			}
			else
				return lexer_string(lexer);
		}
	}
	else
		printf("Unclosed quotes\n");
	return (void*)0;
}

void after_quote(lexer_t *lexer , char *s, char **value)
{
	token_t *token;
	if(!is_whitespace(lexer->c))
	{
		while (lexer->c != '\0')
		{
			if (lexer->c == '"')
			{
				token = lexer_double_quote(lexer);
				*value = strjoin(*value, token->value);
			}
			if (lexer->c == 39)
			{
				token = lexer_single_quote(lexer);
				*value = strjoin(*value, token->value);
			}
			if (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\t')
				break;
			s = lexer_get_current_char_as_string(lexer);
			*value = strjoin(*value, s);
			lexer_advance(lexer);
		}
	}
}
token_t *lexer_double_quote(lexer_t *lexer)// TOKEN_DOUBLE_QUOTE,
{
	char *value;
	char *s;

	lexer_advance(lexer);// cuz we're gonna skip the quote
	value = malloc(sizeof(char));
	while (lexer->c != '"' && lexer->c != '\0')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = strjoin(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	after_quote(lexer , s, &value);
	//printf("valuue ----> %s\n", value);
	return init_token(TOKEN_DOUBLE_QUOTE, value);
}

token_t *lexer_single_quote(lexer_t *lexer)
{
	char *value;
	char *s;
	//token_t *token;

	value = malloc(sizeof(char));
	lexer_advance(lexer);
	while (lexer->c != 39 && lexer->c != '\0')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = strjoin(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	after_quote(lexer, s, &value);
	return init_token(TOKEN_SINGLE_QUOTE, value);
}
token_t *lexer_string(lexer_t *lexer)//Token string
{
	char *value;
	char *s;
	token_t *token;

	value = malloc(sizeof(char));
	while (lexer->c != '\0' && !is_whitespace(lexer->c))
	{
		if (lexer->c == '"')
		{
			token = lexer_double_quote(lexer);
			value = strjoin(value, token->value);
		}
		if (lexer->c == 39)
		{
			token = lexer_single_quote(lexer);
			value = strjoin(value, token->value);
		}
		if (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\t')
			break;
		s = lexer_get_current_char_as_string(lexer);
		value = strjoin(value, s);
		//printf("str  ---->%s\n",value);
		lexer_advance(lexer);
	}
	return init_token(TOKEN_STRING, value);
}
// token_t *lexer_get_next_token(lexer_t *lexer)// 
// {
	
// 	int count = 0;
// 	char *str = lexer->contents;
// 	int i = 0;
// 	//printf("str ---> %s\n",lexer->contents);
// 	//printf("count --> %d\n",count);
// 	//printf("index --> %d\n",i);
// 	//printf("count --> %d\n",count);
// 	//printf("index --> %d\n",i);
// 	//while (str[i])
// 	//{
// 		//if (str[i] == '"')
// 		//	count++;
// 	//	i++;
// 	//}
// 	//if (count % 2 != 0)
// 		//return(init_token(TOKEN_ERR, "Error : Unclosed quotes"));
// 	//else 
// 	//{
// 		while (lexer->c != '\0')
// 		{
// 		//if (count % 2 != 0)
// 		//return(init_token(TOKEN_ERR, "Error : Unclosed quotes"));
// 		while (str[i])
// 		{
// 			if (str[i] == '"')
// 				count++;
// 			i++;
// 		}
// 		if (count % 2 != 0)
// 		{
// 			init_token(TOKEN_ERR, "Error : Unclosed quotes");
// 			return (void*)0;
// 		}
// 		if (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
// 			lexer_skip_whitespace (lexer);
// 		if (lexer->c == '"')
// 			return lexer_double_quote(lexer);
// 		else
// 			return lexer_string(lexer);
// 		}
// 	//}
// 	return (void*)0;
// 	// 	// else if (lexer->c == 39)
// 	// 	// 	return lexer_single_quote(lexer);
// 	// 	// else if (lexer->c == '>')
// 	// 	// {
// 	// 	// 	return (lexer_advace_with_token(lexer, init_token(TOKEN_OUT, lexer_get_current_char_as_string(lexer))));
// 	// 	// 	break;
// 	// 	// }
// 	// 	// else if (lexer->c == '<')
// 	// 	// {
// 	// 	// 	return (lexer_advace_with_token(lexer, init_token(TOKEN_IN, lexer_get_current_char_as_string(lexer))));
// 	// 	// 	break;
// 	// 	// }
// 	// 	// else if (lexer->c == '|')
// 	// 	// {
// 	// 	// 	return (lexer_advace_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
// 	// 	// 	break;
// 	// 	// }
// }

// token_t *lexer_double_quote(lexer_t *lexer)// TOKEN_DOUBLE_QUOTE,
// {
// 	char *value;

// 	lexer_advance(lexer);// cuz we're gonna skip the quote
// 	value = malloc(sizeof(char));
// 	//value[0] = '\0';
// 	// while (lexer->contents[i])
// 	// {
// 	// 	if (lexer->contents[i] == '"')
// 	// 		count++;
// 	// 	i++;
// 	// }
// 	// if (count % 2 != 0)
// 	// 	return (print_err("error"));
// //	{
// 	while (lexer->c != '"' && lexer->c != '\0')
// 	{
// 		char *s = lexer_get_current_char_as_string(lexer);
// 		value = strjoin(value, s);
// 		lexer_advance(lexer);
// 	}
// 	lexer_advance(lexer);
// 	return init_token(TOKEN_DOUBLE_QUOTE, value);
// 	//}
// 	//return init_token(TOKEN_ERR, value);
// 	// if(!is_whitespace(lexer->c))
// 	// {
// 	// 	while (lexer->c != '\0')
// 	// 	{
// 	// 		if (lexer->c == 39|| lexer->c == '"')
// 	// 			lexer_advance(lexer);
// 	// 		else if (is_whitespace(lexer->c))
// 	// 			break;
// 	// 		else 
// 	// 		{
// 	// 			char *s = lexer_get_current_char_as_string(lexer);
// 	// 			strcat(value, s);
// 	// 			lexer_advance(lexer);
// 	// 		}
// 	// 	}
// 	// }
// }


// token_t *lexer_string(lexer_t *lexer)//Token string
// {
// 	char *value;

// 	value = malloc(sizeof(char));
// 	value[0] = '\0';
// 	while (lexer->c != '\0' && is_whitespace(lexer->c) == 0)
// 	{
// 		char *s = lexer_get_current_char_as_string(lexer);
// 		strcat(value, s);
// 		lexer_advance(lexer);
// 	}
// 	return init_token(TOKEN_STRING, value);
// }

// int check_errors(lexer_t *lexer)
// {
// 	int i;
// 	int c_sq;
// 	int c_dq;

// 	i = 0;
// 	c_dq = 0;
// 	c_sq = 0;
// 	while (lexer->contents[i] != '\0')
// 	{
// 		if (lexer->contents[i] == '"')
// 			c_dq++;
// 		if (lexer->contents[i] == 39)
// 			c_sq++;
// 		i++;
// 	}
// 	if(c_dq % 2 == 0 && c_sq % 2 == 0)// make no sc
// 		return(1);
// 	return (printf("error a zen"));
// }


// token_t *lexer_single_quote(lexer_t *lexer)
// {
// 	char *value;

// 	value = malloc(sizeof(char));
// 	value[0] = '\0';
// 	lexer_advance(lexer);
// 	while (lexer->c != 39)
// 	{
// 		char *s = lexer_get_current_char_as_string(lexer);
// 		strcat(value, s);
// 		lexer_advance(lexer);
// 	}
// 	lexer_advance(lexer);
// 	return init_token(TOKEN_SINGLE_QUOTE, value);
// }

// token_t *token_double_quote(t_lexer *lexer)
// {

// }
// void after_double_quote(t_lexer *lexer)
// {

// }