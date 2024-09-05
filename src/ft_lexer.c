/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/09/04 18:03:58 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	if (!input)
		return (NULL);
	i = 0;
	state = NORMAL;
	head = NULL;
	if (ft_tok_need(input))
		return (NULL);
	if (ft_unclosed_quote(input))
		return (NULL);
	while (input[i])
	{
		i = ft_skip_whitespace(input, i);
		if (input[i])
			i = ft_process_tokens(input, &head, &state, i);
	}
	ft_type_helper(head);
	return (head);
}

int	ft_process_tokens(char *input, t_token **head, t_state *state, int start)
{
	int		i;
	char	*tok_str;
	t_token	*token;
	int		m_index;
	bool	quotes;
	t_state	s;

	quotes = false;
	i = start;
	while (input[i] && (*state != NORMAL
			|| !ft_iswhitespace(input[i])) && !ft_issep(input, i))
	{
		*state = ft_handle_state(input[i], *state);
		if (ft_is_in_quotes(input, i, &m_index, input[i]) && !quotes)
		{
			i = m_index;
			quotes = true;
		}
		else
			i++;
	}
	if (start != i)
	{
		tok_str = ft_tokenstr(input, start, i);
		if (ft_isquote(tok_str[0]))
		{
			s = ft_quote_type(tok_str[0]);
			ft_rm_quotes(&tok_str, tok_str[0]);
		}
		else
		{
			ft_rm_quotes(&tok_str, '\'');
			ft_rm_quotes(&tok_str, '"');
		}
		token = ft_token_new(ft_strdup(tok_str));
		free(tok_str);
		token->state = s;
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

t_state	ft_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_Q);
	else if (c == '\"')
		return (DOUBLE_Q);
	else
		return (NORMAL);
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
		printf("char: %c -- state rn: %d -- index: %d\n", str[i], state, i);
		if (state != NORMAL && str[i + 1] == '\0')
		{
			ft_print_err("Syntax error: unclosed quote\n");
			return (1);
		}
		i++;
	}
	return (0);
}
