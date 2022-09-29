#ifndef PARSER_H
# define PARSER_H
#include "lexer.h"

typedef struct s_cmd
{
	char *cmd;
	struct s_cmd *next;
}			t_cmd;

typedef struct s_redir
{
	int type;
	char *file;
	struct s_redir *next;
	
}	t_redir;

typedef struct s_exec
{
	t_cmd	*cmd;
	t_redir	*redir;
	struct s_exec	*next;
}				t_exec;
void parser(t_list *list);
//void parser(token_t *token, lexer_t *lexer);
//void parser(token_t *token, lexer_t *lexer);
//t_exec	*addnode_parser(void *id, void *data);//
void add_back_cmd(t_cmd **lst, t_cmd *new);
void add_back_redir(t_redir **lst, t_redir *new);
void add_back_exec(t_exec **lst, t_exec *new);
void print_list_parser(t_exec *list);//
//void add_back_parser(t_exec **lst, t_exec *new);//
//void add_back_parser(void **lst, void *new);
//void add_back_parser(t_cmd **lst, t_cmd *new);

# endif