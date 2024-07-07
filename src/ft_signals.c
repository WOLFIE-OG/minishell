/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:47 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/07 21:22:33 by ssottori         ###   ########.fr       */
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
	g_var_signal = signum;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ft_sigint_exec(int signum)
{
	g_var_signal = signum;
	write(STDIN_FILENO, "\n", 1);
}

void	ft_config_siginit(void)
{
	signal(SIGINT, ft_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_config_sigquit(void)
{
	signal(SIGINT, ft_sigint_exec);
	signal(SIGQUIT, SIG_IGN);
}
