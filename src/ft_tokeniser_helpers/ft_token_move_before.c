/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_move_before.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:36:42 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 14:54:01 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_move_before(t_token *move_token, t_token *target)
{
	t_token	*temp;

	if (!move_token || !target)
		return ;
	if (move_token == target)
		return ;
	temp = move_token->next;
	if (move_token->prev)
		move_token->prev->next = temp;
	if (temp)
		temp->prev = move_token->prev;
	if (target->prev)
	{
		target->prev->next = move_token;
		move_token->prev = target->prev;
	}
	else
		move_token->prev = NULL;
	move_token->next = target;
	target->prev = move_token;
}
