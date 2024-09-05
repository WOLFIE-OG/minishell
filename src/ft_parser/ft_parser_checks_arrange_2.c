/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_checks_arrange_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:21 by otodd             #+#    #+#             */
/*   Updated: 2024/09/03 18:11:19 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parser_arrange_heredoc_alt(t_root *rt, t_token *i_tkn, t_token **tkn)
{
	i_tkn->str = ft_handle_heredoc(rt, i_tkn);
	ft_token_move_before(i_tkn, *tkn);
	*tkn = i_tkn;
	if (!(*tkn)->prev)
		rt->preped_tokens = *tkn;
}
