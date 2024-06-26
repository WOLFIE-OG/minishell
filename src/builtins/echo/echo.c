/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/06/25 14:12:58 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	echo(t_root *root, char **data)
{
	int		offset;

	offset = 1;
	if (ft_strarraylen(data) > 1)
	{
		if (ft_strrep(data[1], 'n'))
			offset++;
		ft_printf("%A", &data[offset]);
	}
	if (offset != 2)
		printf("\n");
}
