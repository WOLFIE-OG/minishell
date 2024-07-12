/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:08:10 by otodd             #+#    #+#             */
/*   Updated: 2024/07/12 20:40:13 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_token_pop(t_token *node)
{
	int		new_index;
	t_token	*current;

	if (!node)
		return (NULL);
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	new_index = node->index;
	current = node->next;
	while (current)
	{
		current->index = new_index;
		new_index++;
		current = current->next;
	}
	return (node);
}
