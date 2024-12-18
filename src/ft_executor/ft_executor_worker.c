/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 23:57:00 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_worker_handle_child(t_root *root, char *cmd, char **args)
{
	char	**env;

	signal(SIGINT, SIG_DFL);
	if (!ft_handle_worker_pipes(root))
		exit(EXIT_FAILURE);
	env = ft_env_to_array(root, false);
	if (execve(cmd, args, env) == -1)
	{
		free(cmd);
		ft_gc_str_array(env);
		exit(127);
	}
}

static void	ft_worker_handle_parent(t_root *root)
{
	close(root->current_cmd->pipe[1]);
	if (root->prev_cmd)
		close(root->prev_cmd->pipe[0]);
	root->prev_cmd = root->current_cmd;
}

void	ft_worker(t_root *root, char *cmd, char **args)
{
	if (!root->prev_cmd && !root->current_cmd->next)
	{
		close(root->current_cmd->pipe[0]);
		close(root->current_cmd->pipe[1]);
	}
	root->current_cmd->pid = fork();
	if (root->current_cmd->pid == -1)
	{
		perror("fork");
		root->prev_cmd->exit_code = EXIT_FAILURE;
		return ;
	}
	if (root->current_cmd->pid == 0)
		ft_worker_handle_child(root, cmd, args);
	else
		ft_worker_handle_parent(root);
}
