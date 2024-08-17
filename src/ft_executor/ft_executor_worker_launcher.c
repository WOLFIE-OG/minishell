/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker_launcher.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:33:11 by otodd             #+#    #+#             */
/*   Updated: 2024/08/15 17:54:29 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		ft_fprintf(STDERR_FILENO, msg, root->prev_cmd->pid,
			root->prev_cmd_status);
	}
}

static void	ft_worker_failure(t_root *root, bool is_binary)
{
	if (errno == ENOENT && !is_binary)
		ft_fprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			root->current_cmd->cmd_tokens->str);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
			strerror(errno), root->current_cmd->cmd_tokens->str);
	root->prev_cmd_status = errno;
}

static void	ft_worker_path_check(t_root *root, char **cmd, bool *is_binary)
{
	if (ft_is_path_binary(*cmd))
	{
		if (ft_is_path_valid(*cmd, false, false, false))
		{
			if (ft_is_path_valid(*cmd, true, false, false))
			{
				if (ft_is_dir(*cmd))
				{
					*cmd = NULL;
					*is_binary = true;
				}
				else
					*cmd = ft_strdup(root->current_cmd->cmd_tokens->str);
			}
		}
		else
		{
			*cmd = NULL;
			*is_binary = true;
		}
	}
	else
		*cmd = ft_cmd_path(root, root->current_cmd->cmd_tokens->str);
}

void	ft_worker_launcher(t_root *root)
{
	char	*cmd;
	char	**args;
	bool	is_binary;

	is_binary = false;
	args = ft_worker_arg_str(root);
	cmd = root->current_cmd->cmd_tokens->str;
	ft_worker_path_check(root, &cmd, &is_binary);
	if (cmd)
		ft_worker(root, cmd, args);
	else
		ft_worker_failure(root, is_binary);
	ft_gc_str_array(args);
	free(cmd);
	return ;
}
