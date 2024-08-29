/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_checks_arrange.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:21 by otodd             #+#    #+#             */
/*   Updated: 2024/08/29 18:15:32 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_parser_reorder_tokens(
	t_root *rt, t_token *i_tkn, t_token **tkn, t_token *if_tkn)
{
	ft_token_move_before(i_tkn, *tkn);
	ft_token_move_before(if_tkn, i_tkn);
	*tkn = if_tkn;
	if (!(*tkn)->prev)
		rt->preped_tokens = *tkn;
}

void	ft_parser_arrange_input(t_root *rt, t_token *i_tkn, t_token **tkn)
{
	t_token	*if_tkn;

	if_tkn = i_tkn->next;
	ft_parser_reorder_tokens(rt, i_tkn, tkn, if_tkn);
}

void	ft_parser_arrange_heredoc(t_root *rt, t_token *i_tkn, t_token **tkn)
{
	t_token	*if_tkn;

	if_tkn = i_tkn->next;
	if_tkn->str = ft_handle_heredoc(rt, if_tkn->str);
	ft_parser_reorder_tokens(rt, i_tkn, tkn, if_tkn);
}

void	ft_parser_arrange_input_alt(t_root *rt, t_token *i_tkn, t_token **tkn)
{
	ft_token_move_before(i_tkn, *tkn);
	*tkn = i_tkn;
	if (!(*tkn)->prev)
		rt->preped_tokens = *tkn;
}

void	ft_parser_arrange_trunc(t_root *rt, t_token *i_tkn, t_token **tkn)
{
	t_token	*if_tkn;

	if_tkn = i_tkn->next;
	ft_token_move_before(i_tkn, *tkn);
	*tkn = i_tkn;
	if (!(*tkn)->prev)
		rt->preped_tokens = *tkn;
}
