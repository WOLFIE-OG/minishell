/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/06/15 17:07:30 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"

void	echo(char **data)
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
		ft_printf("\n");
}

int	main(int arg_n, char **arg_a)
{
	(void)arg_n;
	echo(arg_a);
	return (EXIT_SUCCESS);
}
