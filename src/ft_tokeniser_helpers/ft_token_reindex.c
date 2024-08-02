/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_reindex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:08:32 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 15:11:05 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_reindex(t_token *token)
{
	int	index;

	index = -1;
	while (token)
	{
		token->index = ++index;
		token = token->next;
	}
}
