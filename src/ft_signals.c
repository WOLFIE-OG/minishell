/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:47 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/18 14:46:39 by otodd            ###   ########.fr       */
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

static void	ft_sigquit_exec(int signum)
{
	write(STDIN_FILENO, "\n", 1);
	(void)signum;
}

void	ft_config_siginit(void)
{
	signal(SIGINT, ft_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_config_sigquit(void)
{
	signal(SIGQUIT, ft_sigquit_exec);
}
