/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:53:06 by otodd             #+#    #+#             */
/*   Updated: 2024/07/31 18:33:22 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_root *root)
{
	const t_token	*arg = ft_find_token_by_index(
			root->current_cmd->cmd_tokens, 1);

	if (ft_unset_var(root, arg->str))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
