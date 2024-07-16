/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:47 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/16 18:30:31 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	octl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line(); - movin to nwl line
	rl_replace_line("", 0); - clearing current input line
*/

static void	ft_sigint_input(int signum)
{
	(void)signum;
	g_var_signal = 130;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, ft_sigint_input);
}

void	ft_config_siginit(void)
{
	signal(SIGINT, ft_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}
