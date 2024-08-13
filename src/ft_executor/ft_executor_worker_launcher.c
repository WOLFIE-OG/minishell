/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker_launcher.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:33:11 by otodd             #+#    #+#             */
/*   Updated: 2024/08/13 14:18:50 by otodd            ###   ########.fr       */
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

static void	ft_worker_exec(t_root *root, char *cmd, char **args)
{
	ft_worker(root, cmd, args);
	if (root->prev_cmd_status != EXIT_SUCCESS)
		ft_worker_error_print(root);
	ft_gc_str_array(args);
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
	root->prev_cmd_status = 127;
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
		ft_worker_exec(root, cmd, args);
	else
		ft_worker_failure(root, args, is_binary);
	free(cmd);
	return ;
}
