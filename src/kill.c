/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:32:42 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/01 16:27:31 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* Kills and exits the shell properly
*/

void	kill_shell(t_root *root, int code)
{
	free_env(root);
	write(1, "\n", 1);
	exit(code);
}

void	ft_free_tokens(t_token *tokens, char *value)
{
	static t_token	*tmp = 0;

	while (tokens)
	{
		tmp = tokens;
		tokens = tmp->next;
		free(value);
		free(tokens);
	}
}
