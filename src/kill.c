/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:32:42 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/20 16:42:22 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* Kills and exits the shell properly
*/

void	kill_shell(void)
{
	ft_freestrarr();
	write(1, "\n", 1);
	exit (0);
}