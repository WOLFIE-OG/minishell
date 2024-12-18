/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:43:51 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/04 18:43:59 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_eof(char *input)
{
	if (input)
		return ;
	printf("exit\n");
}

bool	ft_check_state(t_state current_state)
{
	bool	state;

	state = false;
	if (current_state == NORMAL)
		state = false;
	else if (current_state == SINGLE_Q || current_state == DOUBLE_Q)
		state = true;
	return (state);
}

bool	ft_tok_need(char *input)
{
	ft_eof(input);
	if (input[0] == '\0')
		return (true);
	return (false);
}
