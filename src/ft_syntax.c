/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:35:11 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 18:33:28 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_syntax_check(t_token *head)
{
	while (head)
	{
		if (!head->prev && !head->next && head->is_sep)
			return (head);
		else if (!head->prev)
		{
			if (head->type != INPUT && head->type != CMD && head->type != ARG
				&& head->type != TRUNC && head->type != APPEND
				&& head->type != HEREDOC)
				return (head);
			else if (head->is_sep && (head->next && head->next->is_sep))
				return (head);
		}
		else if (head->type == PIPE && (head->next && head->next->type == PIPE))
			return (head);
		else if ((head->type == TRUNC || head->type == APPEND
				|| head->type == INPUT || head->type == HEREDOC) && !head->next)
			return (head);
		else if (head->type == TRUNC && (head->next
				&& head->next->type == INPUT))
			return (head);
		head = head->next;
	}
	return (NULL);
}
