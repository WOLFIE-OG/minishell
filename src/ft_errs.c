/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:44:46 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/06 01:15:05 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_worker_error_print(t_root *root)
{
	char	*msg;

	if (root->prev_cmd->exit_signaled)
	{
		if (root->prev_cmd->exit_code == SIGSEGV)
			msg = SIG_SEGV;
		else if (root->prev_cmd->exit_code == SIGILL)
			msg = SIG_ILL;
		else if (root->prev_cmd->exit_code == SIGTERM)
			msg = SIG_TERM;
		else if (root->prev_cmd->exit_code == SIGINT)
			msg = SIG_INT;
		else if (root->prev_cmd->exit_code == SIGIOT)
			msg = SIG_IOT;
		else if (root->prev_cmd->exit_code == SIGKILL)
			msg = SIG_KILL;
		else
			msg = SIG;
		if (root->prev_cmd->exit_code != SIGPIPE)
			ft_fprintf(STDERR_FILENO, msg, root->prev_cmd->pid,
				root->prev_cmd->exit_code);
		else
			root->prev_cmd->exit_code = EXIT_SUCCESS;
	}
}

void	ft_worker_failure(t_root *root, bool is_binary)
{
	if (errno == ENOENT && !is_binary && ft_get_var(root, "PATH"))
	{
		root->current_cmd->exit_code = 127;
		ft_fprintf(STDERR_FILENO, "%s: command not found\n",
			root->current_cmd->cmd_tokens->str);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n",
			root->current_cmd->cmd_tokens->str, strerror(errno));
		if (errno == EISDIR)
			root->current_cmd->exit_code = 126;
		else if (errno == ENOENT)
			root->current_cmd->exit_code = 127;
		else
			root->current_cmd->exit_code = errno;
	}
	root->prev_cmd = root->current_cmd;
}
