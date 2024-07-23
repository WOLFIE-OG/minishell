/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/23 17:17:45 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
parse input string and convert to linked list of tokens 
each token should correspond to a type*/

t_token	*ft_tokenizer(char *input)
{
	t_state	state;
	t_token	*head;
	int		i;

	i = 0;
	state = NORMAL;
	head = NULL;
	while (input[i])
	{
		i = ft_skip_whitespace(input, i);
		if (input[i])
			i = ft_process_tokens(input, &head, &state, i);
	}
	return (head);
}

int	ft_process_tokens(char *input, t_token **head, t_state *state, int start)
{
	int		i;
	char	*tok_str;
	t_token	*token;

	i = start;
	while (input[i] && !ft_iswhitespace(input[i]) && !ft_issep(input, i))
	{
		*state = ft_handle_state(input[i], *state);
		i++;
	}
	if (start != i)
	{
		tok_str = ft_tokenstr(input, start, i);
		token = ft_token_new(tok_str);
		ft_token_type(token, 0);
		ft_token_add(head, token);
	}
	if (input[i] && ft_issep(input, i))
		i = ft_parse_tokens(input, i, head);
	else if (input[i])
		i++;
	return (i);
}
//TO DO: mak sure the last token is added if the input ends without a sep

void	ft_test_token(void)
{
	char *testtokens[] = {"", ">", ">>", "<", "|", ";", "cmd", "arg"};
	int num_tests = sizeof(testtokens) / sizeof(testtokens[0]);

	for (int i = 0; i < num_tests; i++)
	{
		t_token *token = ft_token_new(ft_strdup(testtokens[i]));
		ft_token_type(token, 0);
		printf("Token value: '%s' -> Token type: %d\n", token->str, token->type);
		free(token->str);
		free(token);
	}
}

/* Using finite state machine to handle quotes, so tokens are created
ONLY when in NORMAL state or when closing quotes are encountered in
the quoted states. */
t_state	ft_handle_state(char c, t_state current_state)
{
	if (current_state == NORMAL)
	{
		if (c == '\'')
			return (SINGLE_Q);
		if (c == '\"')
			return (DOUBLE_Q);
	}
	else if (current_state == SINGLE_Q && c == '\'')
		return (NORMAL);
	else if (current_state == DOUBLE_Q && c == '\"')
		return (NORMAL);
	return (current_state);
}
