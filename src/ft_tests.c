/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:45:09 by otodd             #+#    #+#             */
/*   Updated: 2024/09/11 14:52:23 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static const char	*token_type_str(t_token_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == ARG)
		return ("ARG");
	else if (type == TRUNC)
		return ("TRUNC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == INPUT)
		return ("INPUT");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == INPUT_FILE)
		return ("INPUT_FILE");
	else if (type == OUTPUT_FILE)
		return ("OUTPUT_FILE");
	else if (type == HEREDOC_DELIM)
		return ("HEREDOC_DELIM");
	else
		return ("EMPTY");
}

void	ft_test_token(void)
{
	const char	*testtokens[]
		= {"", ">", "<<", ">>", "<", "|", "cmd", "arg"};
	const int	num_tests = sizeof(testtokens) / sizeof(testtokens[0]);
	int			i;
	t_token		*token;

	i = 0;
	while (i < num_tests)
	{
		token = ft_token_new(ft_strdup(testtokens[i]));
		ft_token_type(token, 0);
		printf("Token value: '%s' -> Token type: %s\n", token->str,
			token_type_str(token->type));
		free(token->str);
		free(token);
		i++;
	}
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("token value = '%s' -> token type = %s | index = %d\n",
			current->str, token_type_str(current->type), current->index);
		current = current->next;
	}
}

int	tokenizer_tester(int ac, char **av)
{
	int		i;
	t_token	*tokens;

	i = 1;
	tokens = NULL;
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
