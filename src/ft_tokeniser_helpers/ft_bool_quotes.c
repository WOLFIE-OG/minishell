/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:10:49 by ssottori          #+#    #+#             */
/*   Updated: 2024/09/12 13:22:41 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_matching(char *line, int i, int *match_index, char c)
{
	while (line[i++] != '\0')
	{
		if (line[i] == c)
		{
			*match_index = i;
			return (true);
		}
	}
	return (false);
}

bool	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	ft_singlequote(char c)
{
	if (c == '\'')
		return (true);
	return (false);
}

bool	ft_is_in_quotes(char *line, int i, int *match_index, char c)
{
	if (ft_isquote(c) && ft_matching(line, i, match_index, c))
		return (true);
	return (false);
}
