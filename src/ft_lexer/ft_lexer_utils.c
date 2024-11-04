/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:35 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/04 16:37:03 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_process_quotes(char **tok_str, t_state *s)
{
	char	*head;

	head = *tok_str;
	while (*head && !ft_isquote(*head))
		head++;
	if (*head)
	{
		*s = ft_quote_type(*head);
		ft_rm_quotes(tok_str, *head);
	}
}

void	ft_create_token(t_token_info *info, t_token **head)
{
	char	*tok_str;
	t_token	*token;
	t_state	s;

	s = NORMAL;
	if (info->start != info->end)
	{
		tok_str = ft_tokenstr(info->input, info->start, info->end);
		ft_process_quotes(&tok_str, &s);
		token = ft_token_new(ft_strdup(tok_str));
		free(tok_str);
		if (info->input[info->end] != '\0')
		{
			if (!ft_iswhitespace(info->input[info->end])
				&& !ft_issep(info->input, info->end))
				token->is_compound = true;
			else
				token->has_space_trailing = true;
		}
		if (info->start != 0)
			if (!ft_iswhitespace(info->input[info->start - 1])
				&& !ft_issep(info->input, info->start - 1))
				token->is_compound = true;
		token->state = s;
		ft_token_add(head, token);
	}
}

void	ft_quote_backtrack(t_token_info *info, char *input,
			t_token **head)
{
	int	j;

	j = info->end;
	info->end = info->start;
	while (!ft_isquote(input[info->end]))
		info->end++;
	ft_create_token(info, head);
	while (!ft_isquote(input[info->start]))
		info->start++;
	info->end = j + 1;
}