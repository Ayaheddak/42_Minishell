/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/18 02:53:37 by het-tale         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
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

typedef struct s_leaks
{
	void			*leak;
	struct s_leaks	*next;
}	t_leaks;

typedef struct s_global
{
	t_exec	*exec;
	t_env	*env_list;
	t_token	*last_token;
	int		exitstauts;
	int		errorlexer;
	int		errorparser;
	int		hd;
	t_leaks	*g;
}		t_global;

t_global	g_global;

typedef struct s_sort_list
{
	char	*key;
	char	*val;
	int		len;
}	t_sort_list;

/*
	========================== Token ==========================
*/

t_token	*init_token(int type, char *value, int split);
void	print_tokenizer(t_token *token);
t_token	*tokenizer(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
void	free_tokenizer(t_token *token);
int		rd(t_token *token);

/*
	========================== lexer ==========================
*/

t_lexer	*init_lexer(char *contents);
t_token	*redirection(t_lexer *lexer, int type1, int type2, char r);
t_token	*lexer_double_quote(t_lexer *lexer);
t_token	*lexer_string(t_lexer *lexer);
t_token	*expanding(t_lexer *lexer);
t_token	*lexer_advace_with_token(t_lexer *lexer, t_token *token);
t_token	*lexer_single_quote(t_lexer *lexer);
t_token	*lexer_expanding(t_lexer *lexer);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
void	addback(t_token **head, void *value, void *type, int split);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
char	*get_path(char	**env);
char	*freejoin(char *s1, char *s2);
char	*get_expanded(char *value);
t_token	*expanding_before_heredoc(t_lexer *lexer);
void	conditions(t_lexer *lexer, t_token *token, char **value);
/*
	========================== Utils ==========================
*/
int		is_operator(char c);
int		is_whitespace(char c);
int		is_operator_speciaux(char c);
void	*ft_errer(int i);
int		is_redir(t_token *token);
int		needs_splitting(char *str);
char	*conv_char(char c);
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
char	**ft_realloc(char **args, char *str);
int		len_of_array(char **args);

/*
	--------------------Check commands------------
*/
char	*check_command(char *cmd, t_env *env);
char	*get_right_path(t_env *env, char *cmd);
char	*get_right_path_utils(t_path *corr_path, char *cmd, t_env *env);
void	execute_command(t_execute *exec, t_exec *exec_list, t_env *env);
/*
	--------------------create children---------------
*/
void	start_execution(t_exec *exec_list, t_env *env);
void	input_output(int i, t_execute *exec, t_exec *exec_list);
void	read_from_hrdc(pid_t pd, t_exec *exec_list, int temp_fd);
void	here_doc(int *d, t_execute *exec, t_exec *exec_list);
void	ft_error(char *str);
void	close_pipes(t_execute *exec, int n);
void	close_and_free(t_execute exec, int n);
void	file_exist(int *d, t_execute *exec, t_exec *exec_list);
int		get_size(t_exec *lst);

t_exec	*get_list(void);

/*
	----------------------------Builtins------------------------
*/
int		ft_echo(char **args, t_execute *exec);
int		valid_option(char *str);
int		ft_call_builtins(t_exec *head, t_env *env_list, t_execute *exec);
t_env	*change_pwd(t_env *env_list, char *key);
int		ft_change_dir(char **args, t_env *env);
int		ft_env(t_env *env, char **args, t_execute *exec);
void	print_env(t_env *env, t_execute *exec, int d);
char	*join_key_value(char *key, char *value, int d);
int		ft_pwd(char **args, t_execute *exec, t_env *env);
t_env	*remove_list(t_env **env_list, t_env *remove);
int		ft_unset(char **args, t_env *env_iter);
int		ft_export_to_env(t_env *env_list, char **args, t_execute *exec);
int		is_replaced(t_env *env_list, char *search, char *replace);
int		is_valid_arg(char *str);
int		ft_export_to_copy(t_env *env, char **args, t_execute *exec);
int		ft_exit(char **args);
char	**ft_is_contain_equal(t_env *env_list, char **args, int *d, int *i);
void	loop_through_export(t_env *env_list, char **args, int *d, int i);
int		nameless_func(char **args, t_env *env_list, int *d, int *i);
char	**init_split(char *s1, char *s2);
int		is_exist(t_env *env, char *key);
int		ft_isnt_contain_equal(char *args, int *d, int *i);
int		ft_if_valid(char *str, int *d, int *i);
t_env	*ft_sort_env(t_env *env_list);

/*
----------------------------------Signals---------------------
*/
void	ctrl_d(char *input);
void	ctrlback(int d);
void	signals(int d);
int		ctrl_c(void);

void	leaks_removal(t_leaks **leaks, void *ptr);
#endif