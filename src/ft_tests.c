/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:45:09 by otodd             #+#    #+#             */
/*   Updated: 2024/07/29 18:32:12 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static const char *token_type_str(t_token_type type) {
	switch (type) {
		case EMPTY: return ("EMPTY");
		case CMD: return ("CMD");
		case ARG: return ("ARG");
		case TRUNC: return ("TRUNC");
		case APPEND: return ("APPEND");
		case INPUT: return ("INPUT");
		case PIPE: return ("PIPE");
		case END: return ("END");
		default: return ("UNKNOWN");
	}
}

void	ft_test_token(void)
{
	char *testtokens[] = {"", ">", ">>", "<", "|", ";", "cmd", "arg"};
	int num_tests = sizeof(testtokens) / sizeof(testtokens[0]);

	for (int i = 0; i < num_tests; i++)
	{
		t_token *token = ft_token_new(ft_strdup(testtokens[i]));
		ft_token_type(token, 0);
		printf("Token value: '%s' -> Token type: %s\n", token->str, token_type_str(token->type));
		free(token->str);
		free(token);
	}
}

void	print_tokens(t_token *head)
{
	t_token *current = head;
	while (current)
	{
		printf("token value = '%s' -> token type = %s | index = %d\n", current->str, token_type_str(current->type), current->index);
		current = current->next;
	}
}

int	tokenizer_tester(int ac, char **av)
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

void	cmd_list_test(t_root *root)
{
	t_cmd	*cmds;
	t_cmd	*cmds2;
	t_cmd	*cmds3;

	cmds = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	pipe(cmds->pipe);
	cmds->post_action = PIPE;
	cmds->cmd_tokens = root->tokens;
	cmds->next = NULL;
	cmds2 = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	pipe(cmds2->pipe);
	cmds2->post_action = APPEND;
	cmds2->cmd_tokens = ft_tokenizer("lolcat");
	cmds2->next = NULL;
	cmds->next = cmds2;
	cmds3 = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	pipe(cmds3->pipe);
	cmds3->post_action = EMPTY;
	cmds3->cmd_tokens = ft_tokenizer("ifconfig");
	cmds3->next = NULL;
	cmds2->next = cmds3;
	ft_executor(root, cmds);
	ft_gc_tokens(cmds2->cmd_tokens);
	free(cmds2);
	ft_gc_tokens(cmds->cmd_tokens);
	free(cmds);
	ft_gc_tokens(cmds3->cmd_tokens);
	free(cmds3);
}

void	cmd_list_test_2(t_root *root)
{
	t_cmd	*cmds;

	cmds = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	pipe(cmds->pipe);
	cmds->post_action = EMPTY;
	cmds->cmd_tokens = root->tokens;
	cmds->next = NULL;
	ft_executor(root, cmds);
	ft_gc_tokens(cmds->cmd_tokens);
	free(cmds);
}
