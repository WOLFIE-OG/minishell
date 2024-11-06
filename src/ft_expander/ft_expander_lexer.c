/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/05 23:49:37 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
parse input string and convert to linked list of tokens 
each token should correspond to a type*/

static int	ft_expander_find_token_end(t_token *tkn, int start, bool *trailing)
{
	int		i;

	i = start;
	while (tkn->str[i] && !*trailing)
	{
		if (ft_iswhitespace(tkn->str[i]) && tkn->state == NORMAL)
		{
			*trailing = true;
			break ;
		}
		i++;
	}
	return (i);
}

static void	ft_expander_create_token(t_token_info *info, t_token **head,
	bool trailing, t_token *tkn)
{
	char	*tok_str;
	t_token	*token;
	t_token	*token2;

	if (info->start != info->end)
	{
		tok_str = ft_tokenstr(info->input, info->start, info->end);
		token = ft_token_new(ft_strdup(tok_str));
		free(tok_str);
		ft_token_add(head, token);
		if (trailing && tkn->is_compound)
		{
			token2 = ft_token_new(ft_strdup(" "));
			token2->is_compound = true;
			ft_token_add(head, token2);
		}
	}
}

static int	ft_expander_process_tokens(t_token *tkn, t_token **head,
	int start)
{
	int				i;
	t_token_info	info;
	bool			trailing;

	trailing = false;
	i = ft_expander_find_token_end(tkn, start, &trailing);
	info.input = tkn->str;
	info.start = start;
	info.end = i;
	ft_expander_create_token(&info, head, trailing, tkn);
	if (tkn->str[i])
		i++;
	return (i);
}

t_token	*ft_expander_tokenizer(t_token *tkn)
{
	t_token	*head;
	int		i;

	if (!tkn->str)
		return (NULL);
	i = 0;
	head = NULL;
	if (ft_tok_need(tkn->str))
		return (NULL);
	while (tkn->str[i])
	{
		i = ft_skip_whitespace(tkn->str, i);
		if (tkn->str[i])
			i = ft_expander_process_tokens(tkn, &head, i);
	}
	ft_type_helper(head);
	return (head);
}
