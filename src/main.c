/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/09/10 16:20:50 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	g_var_signal;

static void	ft_shell_post_input(t_root *root, char *input)
{
	t_token	*syntax_ctx;

	root->preped_tokens = ft_tokenizer(input);
	print_tokens(root->preped_tokens);
	syntax_ctx = ft_syntax_check(root->preped_tokens);
	if (syntax_ctx)
	{
		ft_fprintf(STDERR_FILENO, SYNTAX_ERROR_MSG, syntax_ctx->str);
		ft_gc_tokens(root->preped_tokens);
		return ;
	}
	ft_parser(root);
	ft_expander(root);
	ft_executor(root);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*tmp;
	t_root	root;

	ft_init_shell(&root, ac, av, envp);
	if (!root.interactive)
		ft_shell_post_input(&root, root.interactive_str);
	while (true && root.interactive)
	{
		tmp = ft_set_prompt(&root);
		input = readline(tmp);
		ft_gc_str_array(root.prompt);
		free(tmp);
		if (!input)
		{
			ft_putstr("exit\n");
			break ;
		}
		ft_shell_post_input(&root, input);
		if (ft_strlen(input))
			add_history(input);
		free(input);
	}
	ft_exit(&root, root.prev_cmd_status);
}
