/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/29 21:45:30 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_var_signal;

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*tmp;
	t_cmd	*cmd;
	t_root	root;

	g_var_signal = 0;
	ft_init_shell(&root, ac, av, envp);
	tokenizer_tester(ac, av);
	ft_config_sigint();
	while (true)
	{
		tmp = ft_set_prompt(&root);
		input = readline(tmp);
		ft_gc_str_array(root.prompt);
		free(tmp);
		// ft_test_token();
		if (!input)
		{
			printf("exit\n"); //handling EOF
			break ;
		}
		root.tokens = ft_tokenizer(input);
		print_tokens(root.tokens);
		cmd = ft_parser(&root);
		ft_executor(&root, cmd);
		// cmd_list_test_2(&root);
		// cmd_list_test(&root);
		add_history(input);
		free(input);
	}
	ft_exit(&root, EXIT_SUCCESS);
}
