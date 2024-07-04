/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:21:21 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 17:12:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_add(t_token **lst, t_token *new_l)
{
	t_token	*tmp;

	if (*lst)
	{
		tmp = ft_token_last(*lst);
		tmp->next = new_l;
		new_l->prev = tmp;
	}
	else
	{
		*lst = new_l;
		new_l->prev = NULL;
	}
	new_l->next = NULL;
}
