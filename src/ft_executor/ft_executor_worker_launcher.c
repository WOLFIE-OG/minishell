/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker_launcher.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:33:11 by otodd             #+#    #+#             */
/*   Updated: 2024/08/13 01:29:41 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_worker_error_print(t_root *root)
{
	if (root->prev_cmd_status_signaled)
	{
		if (root->prev_cmd_status == SIGSEGV)
			ft_fprintf(STDERR_FILENO,
				"[%d] Segmentation fault (core dumped) %d\n",
				root->prev_cmd->pid, root->prev_cmd_status);
		else
			ft_fprintf(STDERR_FILENO, "[%d] Process terminated by signal %d\n",
				root->prev_cmd->pid, root->prev_cmd_status);
	}
}

static void	ft_worker_error_handler(t_root *root, char **args)
{
	if (root->prev_cmd_status != EXIT_SUCCESS)
		ft_worker_error_print(root);
	ft_gc_str_array(args);
	return ;
}

static void	ft_worker_exec(t_root *root, char *cmd, char **args)
{
	ft_worker(root, cmd, args);
	ft_worker_error_handler(root, args);
}

static void	ft_worker_failure(t_root *root, char **args, bool is_binary)
{
	if (errno == ENOENT && !is_binary)
		ft_fprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			root->current_cmd->cmd_tokens->str);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
			strerror(errno), root->current_cmd->cmd_tokens->str);
	ft_gc_str_array(args);
	root->prev_cmd_status = errno;
}

void	ft_worker_launcher(t_root *root)
{
	char	*cmd;
	char	**args;
	bool	is_binary;

	is_binary = false;
	args = ft_worker_arg_str(root);
	cmd = root->current_cmd->cmd_tokens->str;
	if (ft_is_path_binary(cmd))
	{
		if (ft_is_path_valid(cmd, false, false, false))
		{
			if (!ft_is_path_valid(cmd, true, false, false))
			{
				cmd = NULL;
				is_binary = true;
			}
			if (ft_is_dir(cmd))
				cmd = NULL;
		}
		else
		{
			cmd = NULL;
			is_binary = true;
		}
	}
	else
		cmd = ft_cmd_path(root, root->current_cmd->cmd_tokens->str);
	if (cmd)
		ft_worker_exec(root, cmd, args);
	else
		ft_worker_failure(root, args, is_binary);
	return ;
}
