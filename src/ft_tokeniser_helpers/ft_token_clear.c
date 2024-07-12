/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:21:21 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 16:43:31 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_clear(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;
	t_token	*tmp_2;

	tmp = *lst;
	while (tmp)
	{
		tmp_2 = tmp->next;
		ft_token_delone(tmp, del);
		tmp = tmp_2;
	}
	*lst = NULL;
}
