/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:51 by otodd             #+#    #+#             */
/*   Updated: 2024/06/28 17:23:54 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_space(char *input, int i)
{
	int	j;

	j = 0;
	while (ft_iswhitespace(input[i + j]))
		j++;
	return (j);
}
