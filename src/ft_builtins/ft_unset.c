/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:53:06 by otodd             #+#    #+#             */
/*   Updated: 2024/11/08 16:43:27 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_root *root)
{
	t_token	*args;

	args = root->current_cmd->cmd_tokens;
	if (args && !args->next)
		return (EXIT_SUCCESS);
	args = args->next;
	while (args)
	{
		ft_unset_var(root, args->str);
		args = args->next;
	}
	return (EXIT_SUCCESS);
}
