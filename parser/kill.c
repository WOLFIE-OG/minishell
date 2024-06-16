/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:32:42 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/16 14:01:13 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Kills and exits the shell properly
*/

void	kill_shell(void)
{
	ft_freestrarr();
	write(1, "\n", 1);
	exit (0);
}