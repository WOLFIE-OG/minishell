/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/09/23 14:37:37 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_handle_compounds(t_root *root)
{
	t_cmd	*head_c;
	t_token	*head_t;
	t_token	*c_head_t;
	t_token	*next_token;
	char	*tmp;

	head_c = root->preped_cmds;
	while (head_c)
	{
		head_t = head_c->cmd_tokens;
		while (head_t)
		{
			if (head_t->is_compound)
			{
				c_head_t = head_t;
				while (head_t && head_t->is_compound)
				{
					if (head_t == c_head_t)
					{
						head_t = head_t->next;
						continue ;
					}
					tmp = ft_strjoin(c_head_t->str, head_t->str);
					free(c_head_t->str);
					c_head_t->str = tmp;
					if (head_t->has_space_trailing)
						c_head_t = head_t->next;
					next_token = head_t->next;
					ft_token_delone(ft_token_pop(head_t), free);
					head_t = next_token;
				}
			}
			else
				head_t = head_t->next;
		}
		head_c = head_c->next;
	}
}

static void	ft_shell_post_input(t_root *root, char *input)
{
	t_token	*syntax_ctx;

	root->preped_tokens = ft_tokenizer(input);
	if (DEBUG)
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
	ft_handle_compounds(root);
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
