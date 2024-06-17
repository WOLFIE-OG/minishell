/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:47 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/16 13:42:56 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	sigint_input(int signum)
{
	gvar_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0); //clearing current input line
	rl_on_new_line(); //movin to nwl line
}

static void	sigint_exec(int signum)
{
	gvar_signal = signum;
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