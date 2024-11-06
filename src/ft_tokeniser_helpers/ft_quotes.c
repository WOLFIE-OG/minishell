/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:59:28 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/06 01:15:56 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Using finite state machine to handle quotes, so tokens are created
ONLY when in NORMAL state or when closing quotes are encountered in
the quoted states. */

t_state	ft_handle_state(char c, t_state current_state)
{
	if (current_state == NORMAL)
	{
		if (c == '\'')
			return (SINGLE_Q);
		if (c == '\"')
			return (DOUBLE_Q);
	}
	else if (current_state == SINGLE_Q && c == '\'')
		return (NORMAL);
	else if (current_state == DOUBLE_Q && c == '\"')
		return (NORMAL);
	return (current_state);
}

t_state	ft_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_Q);
	else if (c == '\"')
		return (DOUBLE_Q);
	else
		return (NORMAL);
}

int	ft_unclosed_quote(char *str)
{
	int		i;
	t_state	state;

	i = 0;
	state = NORMAL;
	while (str[i])
	{
		state = ft_handle_state(str[i], state);
		if (DEBUG)
			printf("char: %c -- state rn: %d -- index: %d\n", str[i], state, i);
		if (state != NORMAL && str[i + 1] == '\0')
		{
			ft_fprintf(STDERR_FILENO, "Syntax error: unclosed quote\n");
			return (1);
		}
		i++;
	}
	return (0);
}
