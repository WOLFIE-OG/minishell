/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/04 15:17:02 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
parse input string and convert to linked list of tokens 
each token should correspond to a type*/

static int	ft_expander_find_token_end(char *input, int start)
{
	int		i;

	i = start;
	while (input[i] && (!ft_iswhitespace(input[i])))
		i++;
	return (i);
}

static void	ft_expander_create_token(t_token_info *info, t_token **head)
{
	char	*tok_str;
	t_token	*token;

	if (info->start != info->end)
	{
		tok_str = ft_tokenstr(info->input, info->start, info->end);
		token = ft_token_new(ft_strdup(tok_str));
		free(tok_str);
		ft_token_add(head, token);
	}
}

static int	ft_expander_process_tokens(char *input, t_token **head,
	int start)
{
	int				i;
	t_token_info	info;

	i = ft_expander_find_token_end(input, start);
	info.input = input;
	info.start = start;
	info.end = i;
	ft_expander_create_token(&info, head);
	if (input[i])
		i++;
	return (i);
}

t_token	*ft_expander_tokenizer(char *input)
{
	t_token	*head;
	int		i;

	if (!input)
		return (NULL);
	i = 0;
	head = NULL;
	if (ft_tok_need(input))
		return (NULL);
	while (input[i])
	{
		i = ft_skip_whitespace(input, i);
		if (input[i])
			i = ft_expander_process_tokens(input, &head, i);
	}
	ft_type_helper(head);
	return (head);
}
