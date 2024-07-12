/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/12 18:42:10 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_root *root)
{
	char			**temp;
	const t_token	*arg = ft_find_token_by_index(root, 1);

	if (!arg)
		return ;
	temp = ft_key_value(arg->str, '=');
	if (temp[1])
		ft_set_var(root, temp[0], temp[1]);
	free(temp[0]);
	free(temp);
}
