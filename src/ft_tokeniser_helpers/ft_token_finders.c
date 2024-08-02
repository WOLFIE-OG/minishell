/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_finders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:11:29 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 16:11:51 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_get_token_by_type_at_i(t_token *tkns, t_token_type type, int index)
{
	t_token	*head;

	head = tkns;
	while (head)
	{
		if (head->type == type && head->index == index)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_token	*ft_find_token_by_index(t_token *tokens, int index)
{
	t_token	*head;

	head = tokens;
	while (head)
	{
		if (head->index == index)
			return (head);
		head = head->next;
	}
	return (NULL);
}
