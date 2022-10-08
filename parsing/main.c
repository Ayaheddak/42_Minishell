/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/08 23:33:02 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_traverse_redir(t_redir *red)
{
	while (red)
	{
		printf("Type : %d\nName : %s\n", red->type, red->name);
		red = red->next;
	}
}

void	ft_traverse_exec(t_exec *exec)
{
	int	i;
	int	j;

	j = 0;
	while (exec)
	{
		i = 0;
		printf("-------arguments of %d node ----\n", j + 1);
		while (exec->args[i])
		{
			printf("arg number %d: %s\n", i, exec->args[i]);
			i++;
		}
		while (exec->redir)
		{
			printf("------Redirections of %d node----\n", j + 1);
			printf("The redirection type: %d,\nThe redirection value: %s\n", exec->redir->type, exec->redir->name);
			exec->redir = exec->redir->next;
		}
		j++;
		exec = exec->next;
	}
}

int main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token *token;
	t_env	*env_list;
	//t_exec	*exec_l;
	pid_t pid;
	int	status;
	
	(void)argc;
	(void)argv;
	(void)env;
	while (1) 
	{
		inpt = readline("./minishell$ ");
		if (!inpt)
			continue;
		lexer_t *lexer = init_lexer(inpt);
		add_history(inpt);
		token = tokenizer(lexer);
		g_global.exec = parser(token);
		// ft_traverse_redir(g_global.exec->redir);
		//exec_l = get_list();
		env_list = get_env_list(env);
		if (g_global.errorlexer == 1)
		{
			free_tokenizer(token);
			g_global.errorlexer = 0;
			continue ;
		}
		if (g_global.errorparser == 1)
		{
			free_tokenizer(token);
			free_exec(g_global.exec);
			g_global.errorparser = 0;
			continue ;
		}
		pid = fork();
		if (!pid)
			start_execution(g_global.exec, env_list);
		waitpid(pid, &status, 0);
		//printf("here\n");
		// print_redir(g_global.exec->redir);
		// ft_traverse_exec(g_global.exec);
		// system("leaks minishell");
	}
	return (0);
}

// t_exec *parser(t_token *head)
// {
// 	t_token *token;
// 	t_exec *exec;

// 	check_parse_errors(head);
// 	token = head;
// 	exec = alocate_exec();
// 	while(token)
// 	{
// 		if (token == NULL)
// 		{
// 			exec->next = NULL;
// 			break;
// 		}
// 		if (token->type == TOKEN_PIPE)
// 		{
// 			exec->next = parser(token->next);
// 			break;
// 		}
// 		if (token->type == TOKEN_STRING)
// 			exec->args = ft_realloc(exec->args,token->value);
// 		if (is_redir(token) != 0)
// 		{
// 			addredirection(&exec->redir,is_redir(token),token->next->value);
// 			token = token->next;
// 		}
// 		token = token->next;
// 	}
// 	//print_redir(exec->redir);
// 	return exec;
// }
