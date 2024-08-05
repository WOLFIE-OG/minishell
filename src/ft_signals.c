/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:47 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/05 13:14:50 by otodd            ###   ########.fr       */
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

static void	ft_sigint_cmd(int signum)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(signum);
}

void	ft_config_sigint(void)
{
	signal(SIGINT, ft_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_config_sigint_cmd(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, ft_sigint_cmd);
}
