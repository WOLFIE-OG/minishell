/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:43:51 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/17 17:03:49 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_eof(char *input)
{
	if (input)
		return ;
	ft_printf("exit\n");
	//need to exit minish here
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

bool	ft_dollar_sign(char *input)
{
	while (ft_iswhitespace(*input))
		input++;
	if (!(*input))
		return (false);
	if (*input == '$')
		input++;
	while (ft_iswhitespace(*input))
		input++;
	if (*input != '\0')
		return (false);
	ft_putstr_fd("minishell: $: command not found\n", STDERR_FILENO);
	return (true);
}

bool	ft_tok_need(char *input)
{
	ft_eof(input);
	if (input[0] == '\0')  // Empty line check
		return (true);
	if (ft_dollar_sign(input))  // Single dollar sign check
		return (true);
	return (false);
}

//TODO
//fix dollarsign error and tokneed