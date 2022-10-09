/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/09 01:14:55 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include "libft.h"
# include "token.h"
# include "lexer.h"
# include "env.h"
# include "execute.h"
# define BUFFER_SIZE 42

typedef struct s_redir
{
	int				type;
	char			*name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	char			**args;
	t_redir			*redir;
	struct s_exec	*next;
}				t_exec;

typedef struct s_global
{
	t_exec	*exec;
	char	**env;
	int		exitstauts;
	int		errorlexer;
	int		errorparser;
}		t_global;

t_global	g_global;

/*
	========================== Token ==========================
*/

t_token	*init_token(int type, char *value);
void	print_tokenizer(t_token *token);
t_token	*tokenizer(lexer_t *lexer);
t_token	*lexer_get_next_token(lexer_t *lexer);
void	free_tokenizer(t_token *token);

/*
	========================== lexer ==========================
*/

lexer_t	*init_lexer(char *contents);
t_token	*redirection(lexer_t *lexer, int type1, int type2, char r);
t_token	*lexer_double_quote(lexer_t *lexer);
t_token	*lexer_string(lexer_t *lexer);
t_token	*expanding(lexer_t *lexer);
t_token	*lexer_advace_with_token(lexer_t *lexer, t_token *token);
t_token	*lexer_single_quote(lexer_t *lexer);
t_token	*lexer_expanding(lexer_t *lexer);
void	lexer_advance(lexer_t *lexer);
void	lexer_skip_whitespace(lexer_t *lexer);
void	addback(t_token **head, void *value, void *type);
char	*lexer_get_current_char_as_string(lexer_t *lexer);
char	*get_path(char	**env);
char	*freejoin(char *s1, char *s2);
char	*get_exapanded_test(void);//
int		is_operator(char c);
int		is_whitespace(char c);
int		is_operator_speciaux(char c);
/*
	========================== Error ==========================
*/

void	*ft_errer(int i);

/*
	========================== Parser ==========================
*/
int		is_op(t_token *token);
void	*check_parse_errors(t_token *head);
t_exec	*alocate_exec(void);
t_exec	*parser(t_token *head);
void	addredirection(t_redir **head, int type, char *file);
void	print_redir(t_redir *redir);
void	free_exec(t_exec *exec);
/*---------------get_next_line------------------------*/
char	*get_next_line(int fd);
char	*extract_line(char *str);
char	*extract_after_line(char *str);
char	*ft_read(int *rb, char *temp, char *buf, int fd);
char	*ft_cpy(char *str, int *i, int *j);
void	skip_line(char *str, int *j);

/*--------------------Check commands------------*/
char	*check_command(char *cmd, t_env *env);
char	*get_right_path(t_env *env, char *cmd);
char	*get_right_path_utils(t_path *corr_path, char *cmd, t_env *env);
void	execute_command(t_execute *exec, char **cmd, t_env *env);
/*--------------------create children---------------*/
void	start_execution(t_exec *exec_list, t_env *env);
void	input_output(int i, t_execute *exec, t_exec *exec_list);
void	ft_error(char *str);
void	close_pipes(t_execute *exec, int n);
void	close_and_free(t_execute exec, int n);
void	file_exist(int *d, t_execute *exec, t_exec *exec_list);
int		get_size(t_exec *lst);

t_exec	*get_list(void);
#endif