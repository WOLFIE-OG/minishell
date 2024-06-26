/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:47 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/25 14:27:35 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sigint_input(int signum)
{
	g_var_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0); //clearing current input line
	rl_on_new_line(); //movin to nwl line
}

static void	sigint_exec(int signum)
{
	g_var_signal = signum;
	write(1, "\n", 1);
}

void	config_siginit(void)
{
	signal(SIGINT, sigint_input);
	signal(SIGQUIT, SIG_IGN);
}

void	config_sigquit(void)
{
	signal(SIGINT, sigint_exec);
	signal(SIGQUIT, SIG_IGN);
}
