/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/15 13:16:58 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char	*token_type_str(t_token_type type);

/*
parse input string and convert to linked list of tokens 
each token should correspond to a type*/

static void	ft_type_helper(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		ft_token_type(tmp, 0);
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp)
	{
		ft_token_retype(tmp);
		tmp = tmp->next;
	}
}

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
	if (ft_unclosed_quote(input))
		ft_print_err("Syntax error: unclosed quote\n");
	ft_type_helper(head);
	return (head);
}

int	ft_process_tokens(char *input, t_token **head, t_state *state, int start)
{
	int		i;
	char	*tok_str;
	t_token	*token;

	i = start;
	while (input[i] && (*state != NORMAL
			|| !ft_iswhitespace(input[i])) && !ft_issep(input, i))
	{
		*state = ft_handle_state(input[i], *state);
		i++;
	}
	if (start != i)
	{
		tok_str = ft_tokenstr(input, start, i);
		token = ft_token_new(ft_trim_start_end(tok_str, "\"'"));
		free(tok_str);
		ft_token_add(head, token);
	}
	if (*state == NORMAL && input[i] && ft_separator(input[i]))
		i = ft_parse_tokens(input, i, head);
	else if (input[i])
		i++;
	return (i);
}
//TO DO: mak sure the last token is added if the input ends without a sep

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

bool	ft_check_state(t_state current_state)
{
	bool	state;

	state = false;
	if (current_state == NORMAL)
		state = false;
	else if (current_state == SINGLE_Q || current_state == DOUBLE_Q)
		state = true;
	return (state);
}

int	ft_unclosed_quote(char *str)
{
	int		i;
	t_state	state;

	i = 0;
	state = NORMAL;
	while (str[i])
	{
		state = ft_handle_state(str[i], state);
		printf("char: %c -- state rn: %d\n", str[i], state);
		i++;
	}
	if (state != NORMAL)
		ft_print_err("Syntax error: unclosed quote\n");
	return (state != NORMAL);
}
