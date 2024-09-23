/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:06:25 by otodd             #+#    #+#             */
/*   Updated: 2024/09/18 01:32:48 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_token_dup(t_token *token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = ft_strdup(token->str);
	node->type = token->type;
	node->next = NULL;
	node->prev = NULL;
	node->index = 0;
	node->state = token->state;
	node->is_sep = token->is_sep;
	node->is_compound = token->is_compound;
	node->has_space_trailing = token->has_space_trailing;
	return (node);
}
