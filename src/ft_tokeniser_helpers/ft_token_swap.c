/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:50:16 by otodd             #+#    #+#             */
/*   Updated: 2024/07/30 15:58:05 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_swap(t_token *token1, t_token *token2)
{
	t_token	*token1_prev;
	t_token	*token1_next;
	t_token	*token2_prev;
	t_token	*token2_next;
	int		token1_index;

	token1_prev = token1->prev;
	token1_next = token1->next;
	token2_prev = token2->prev;
	token2_next = token2->next;
	token1->prev = token2_prev;
	token1->next = token2_next;
	token2->prev = token1_prev;
	token2->next = token1_next;
	if (token1_prev)
		token1_prev->next = token2;
	if (token1_next)
		token1_next->prev = token2;
	if (token2_prev)
		token2_prev->next = token1;
	if (token2_next)
		token2_next->prev = token1;
	token1_index = token1->index;
	token1->index = token2->index;
	token2->index = token1_index;
}
