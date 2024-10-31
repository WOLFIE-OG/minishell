/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:44:46 by ssottori          #+#    #+#             */
/*   Updated: 2024/10/31 01:31:48 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_err(const char *message)
{
	char	*msg;

	msg = ft_strjoin("minishell: ", message);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
}

void	ft_worker_error_print(t_root *root)
{
	char	*msg;

	if (root->prev_cmd_status_signaled)
	{
		if (root->prev_cmd_status == SIGSEGV)
			msg = SIG_SEGV;
		else if (root->prev_cmd_status == SIGILL)
			msg = SIG_ILL;
		else if (root->prev_cmd_status == SIGTERM)
			msg = SIG_TERM;
		else if (root->prev_cmd_status == SIGINT)
			msg = SIG_INT;
		else if (root->prev_cmd_status == SIGIOT)
			msg = SIG_IOT;
		else if (root->prev_cmd_status == SIGKILL)
			msg = SIG_KILL;
		else
			msg = SIG;
		if (root->prev_cmd_status != SIGPIPE)
			ft_fprintf(STDERR_FILENO, msg, root->prev_cmd->pid,
				root->prev_cmd_status);
	}
}

void	ft_worker_failure(t_root *root, bool is_binary)
{
	if (errno == ENOENT && !is_binary && ft_get_var(root, "PATH"))
	{
		root->prev_cmd_status = 127;
		ft_fprintf(STDERR_FILENO, "%s: command not found\n",
			root->current_cmd->cmd_tokens->str);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
			root->current_cmd->cmd_tokens->str, strerror(errno));
		if (errno == EISDIR)
			root->prev_cmd_status = 126;
		else if (errno == ENOENT)
			root->prev_cmd_status = 127;
		else
			root->prev_cmd_status = errno;
	}
}
