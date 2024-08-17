/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:08:10 by otodd             #+#    #+#             */
/*   Updated: 2024/08/15 15:31:07 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_insert(t_token *node, t_token *target_node)
{
	int		new_index;
	t_token	*current;

	if (!node || !target_node)
		return ;
	node->next = target_node;
	node->prev = target_node->prev;
	if (target_node->prev)
		target_node->prev->next = node;
	target_node->prev = node;
	new_index = node->index;
	current = node->next;
	while (current)
	{
		current->index = new_index;
		new_index++;
		current = current->next;
	}
	return ;
}
