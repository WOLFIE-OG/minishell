/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/04 16:35:28 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
parse input string and convert to linked list of tokens 
each token should correspond to a type*/

static int	ft_find_token_end(char *input, t_state *state, int start)
{
	int		i;
	int		m_index;
	bool	quotes;

	i = start;
	quotes = false;
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
		{
			if (quotes)
				return (i);
			i++;
		}
	}
	return (i);
}

static int	ft_process_tokens(char *input, t_token **head,
				t_state *state, int start)
{
	int				i;
	t_token_info	info;

	i = ft_find_token_end(input, state, start);
	info.input = input;
	info.start = start;
	info.end = i;
	if (ft_isquote(input[info.end]) && !ft_isquote(input[info.start]))
		ft_quote_backtrack(&info, input, head);
	else if (ft_isquote(input[info.end]) && ft_isquote(input[info.start]))
		info.end++;
	ft_create_token(&info, head);
	if (*state == NORMAL && input[i] && ft_separator(input[i]))
		i = ft_parse_tokens(input, i, head);
	else if (input[i])
		i++;
	return (i);
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
