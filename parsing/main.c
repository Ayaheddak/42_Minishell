/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/08 14:25:01 by het-tale         ###   ########.fr       */
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

int main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token *token;
	t_env	*env_list;
	t_exec	*exec_l;
	
	(void)argc;
	(void)argv;
	while (1) 
	{
		inpt = readline("./minishell$ ");
		if (!inpt)
			continue;
		lexer_t *lexer = init_lexer(inpt);
		add_history(inpt);
		token = tokenizer(lexer);
		// g_global.exec = parser(token);
		// ft_traverse_redir(g_global.exec->redir);
		exec_l = get_list();
		env_list = get_env_list(env);
		start_execution(exec_l, env_list);
		// if (g_global.errorlexer == 1)
		// {
		// 	free_tokenizer(token);
		// 	g_global.errorlexer = 0;
		// 	continue ;
		// }
		// if (g_global.errorparser == 1)
		// {
		// 	free_tokenizer(token);
		// 	free_exec(g_global.exec);
		// 	g_global.errorparser = 0;
		// 	continue ;
		// }
		// system("leaks minishell");
	}
	return (0);
}