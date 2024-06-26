/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/06/26 13:50:22 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_root *root, char *data)
{
	char	**temp;

	temp = ft_key_value(data, '=');
	if (temp[1])
		set_var(root, temp[0], temp[1]);
	free(temp[0]);
	free(temp);
}
