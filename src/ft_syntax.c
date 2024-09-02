/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:35:11 by otodd             #+#    #+#             */
/*   Updated: 2024/09/02 17:03:19 by otodd            ###   ########.fr       */
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
		}
		else if (!head->next && (head->is_sep && head->type != END))
			return (head);
		else if (head->next && head->next->type == END && head->is_sep)
			return (head);
		head = head->next;
	}
	return (NULL);
}
