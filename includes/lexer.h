#ifndef LEXER_H
#define LEXER_H

typedef struct lexer_s
{
	char			c;
	unsigned int	i;
	char			*contents;//the source code that we're gonna parce
}	lexer_t;


typedef struct s_list
{
	void	*data;
	void	*id;
	struct s_list *next;

} 	t_list;

lexer_t	*init_lexer(char *contents);
void lexer_advance(lexer_t *lexer);//going to move our pointer to the next character in the content
void lexer_skip_whitespace(lexer_t *lexer);
token_t *lexer_get_next_token(lexer_t *lexer);// func to get next token in the contents
token_t *lexer_double_quote(lexer_t *lexer);
token_t *lexer_string(lexer_t *lexer);
token_t *expanding(lexer_t *lexer);
token_t *lexer_advace_with_token(lexer_t *lexer, token_t *token);
token_t *lexer_single_quote(lexer_t *lexer);
char *lexer_get_current_char_as_string(lexer_t *lexer); //this func is going to return this "char c" but as a string (whhhhhhhy !!!!!!)
char	*get_path(char	**env);
int get_size(t_list *lst);
void add_front(t_list **lst, t_list *new);
void print_list(t_list *list);
void add_back(t_list **lst, t_list *new);
t_list	*addnode(void *id, void *data);
int	is_operator(char c);
int	is_whitespace(char c);
token_t *redirection(lexer_t *lexer, int type1, int type2, char r);
t_list  *get_list(int argc, char *argv[]);//
t_list	*get_env(char *env[]);
char	*get_exapanded_test(void);
token_t *lexer_expanding(lexer_t *lexer);
int	is_operator_speciaux(char c);
void check_err_in_tokens(t_list *list);//
# endif