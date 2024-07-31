/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/31 18:33:36 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_root *root)
{
	char			**temp;
	const t_token	*arg = ft_find_token_by_index(
			root->current_cmd->cmd_tokens, 1);

	if (!arg)
	{
		ft_env(root);
		return (EXIT_SUCCESS);
	}
	temp = ft_key_value(arg->str, '=');
	if (temp[1] && ft_strlen(temp[0]))
		ft_set_var(root, temp[0], temp[1]);
	free(temp[0]);
	free(temp);
	return (EXIT_SUCCESS);
}
