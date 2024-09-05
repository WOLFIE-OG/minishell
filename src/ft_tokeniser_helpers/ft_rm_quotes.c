/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:51 by ssottori          #+#    #+#             */
/*   Updated: 2024/09/05 17:03:51 by ssottori         ###   ########.fr       */
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

void	ft_rm_quotes_in_str(char **value, int start, int end)
{
	char	*tmp;
	char	*trimmed;

	if (!*value || start >= end)
		return ;
	tmp = ft_substr(*value, start, end - start);
	if (!tmp)
		return ;
	trimmed = ft_strtrim(tmp, "\"'");
	free(tmp);
	ft_memcpy(*value + start, trimmed, ft_strlen(trimmed));
	free(trimmed);
}
