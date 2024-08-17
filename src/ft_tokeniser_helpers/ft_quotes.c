/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:59:28 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/17 15:06:36 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_matching(char *line, int i, int *match_index, char c)
{
	while (line[i++] != '\0')
	{
		if (line[i] == c)
		{
			*match_index = i;
			return (TRUE);
		}
	}
	return (FALSE);
}

bool	ft_isquote(char c)
{
	if (c == SINGLE_Q || c == DOUBLE_Q)
		return (TRUE);
	return (FALSE);
}

bool	ft_singlequote(char c)
{
	if (c == SINGLE_Q)
		return (TRUE);
	return (FALSE);
}

bool	ft_is_in_quotes(char *line, int i, int *match_index, char c)
{
	if (ft_isquote(c) && ft_matching(line, i, match_index, c))
		return (TRUE);
	return (FALSE);
}

void	ft_rm_quotes(char **value, char quote)
{
	char	*temp;

	temp = ft_strtrim(*value, &quote);
	free(*value);
	*value = temp;
}