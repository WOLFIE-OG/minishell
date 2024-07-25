/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/25 17:55:22 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_var_signal;

const char *token_type_str(t_token_type type);

static void	print_tokens(t_token *head)
{
	t_token *current = head;
	while (current)
	{
		printf("token value = '%s' -> token type = %s | index = %d\n", current->str, token_type_str(current->type), current->index);
		current = current->next;
	}
}

static int	tokenizer_tester(int ac, char **av)
{
	int i = 1;
	t_token *tokens = NULL;

	if (ac > 1)
	{
		while (i < ac)
		{
			printf("input = %s\n", av[i]);
			tokens = ft_tokenizer(av[i]);
			print_tokens(tokens);
			ft_gc_tokens(tokens);
			printf("\n");
			i++;
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*tmp;
	t_cmd	*cmds;
	// t_cmd	*cmds2;
	// t_cmd	*cmds3;
	t_root	root;

	g_var_signal = 0;
	ft_init_shell(&root, ac, av, envp);
	tokenizer_tester(ac, av);
	ft_config_siginit();
	ft_config_sigquit();
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

		/*TEMP STUFF!!!!*/
		cmds = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		pipe(cmds->io_out);
		cmds->post_action = EMPTY;
		cmds->cmd_tokens = root.tokens;
		cmds->next = NULL;

		// cmds2 = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		// pipe(cmds2->io_out);
		// cmds2->post_action = END;
		// cmds2->cmd_tokens = ft_tokenizer("wc -l");
		// cmds2->next = NULL;
		// cmds->next = cmds2;

		// cmds3 = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		// pipe(cmds3->io_out);
		// cmds3->post_action = EMPTY;
		// cmds3->cmd_tokens = ft_tokenizer("ifconfig");
		// cmds3->next = NULL;
		// cmds2->next = cmds3;
		ft_executor(&root, cmds);
		// ft_gc_tokens(cmds2->cmd_tokens);
		// free(cmds2);
		ft_gc_tokens(cmds->cmd_tokens);
		free(cmds);
		// ft_gc_tokens(cmds3->cmd_tokens);
		// free(cmds3);
		add_history(input);
		free(input);
	}
	ft_exit(&root, EXIT_SUCCESS);
}
