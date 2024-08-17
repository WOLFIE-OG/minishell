/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_move_before.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:36:42 by otodd             #+#    #+#             */
/*   Updated: 2024/08/15 15:30:51 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_move_before(t_token *move_token, t_token *target)
{
	t_token	*tmp;

	if (move_token == target || !move_token || !target)
		return ;
	tmp = ft_token_pop(move_token);
	if (!tmp)
		return ;
	ft_token_insert(tmp, target);
}
