/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeniser_gc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:25:45 by otodd             #+#    #+#             */
/*   Updated: 2024/07/25 16:31:11 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_gc_tokens(t_token *head)
{
	t_token *current = head;
	t_token *next;

	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}
