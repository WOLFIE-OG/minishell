/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:51 by ssottori          #+#    #+#             */
/*   Updated: 2024/09/13 14:27:55 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_rm_quotes(char **value, char quote)
{
	char	*src;
	char	*dst;

	src = *value;
	dst = *value;
	while (*src != '\0')
	{
		if (*src != quote)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

