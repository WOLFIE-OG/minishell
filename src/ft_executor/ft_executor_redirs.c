/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:56:56 by otodd             #+#    #+#             */
/*   Updated: 2024/07/30 14:36:00 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_handler_additonal_worker_pipes(t_root *root)
{
	if (close(root->current_cmd->pipe[0]) == -1)
	{
		perror("error closing pipe[0]");
		return (false);
	}
	if (dup2(root->current_cmd->pipe[1], STDOUT_FILENO) == -1)
	{
		perror("error duplicating pipe[1] to STDIN");
		return (false);
	}
	if (close(root->current_cmd->pipe[1]) == -1)
	{
		perror("error closing pipe[1]");
		return (false);
	}
	return (true);
}

bool	ft_handle_worker_pipes(t_root *root)
{
	if (root->last_executed_cmd)
	{
		if (root->last_executed_cmd->post_action == PIPE || root->last_executed_cmd->post_action == INPUT)
		{
			if (dup2(root->last_executed_cmd->pipe[0], STDIN_FILENO) == -1)
			{
				perror("error duplicating last pipe[0] to STDIN");
				return (false);
			}
			if (close(root->last_executed_cmd->pipe[0]) == -1)
			{
				perror("error closing last pipe[0]");
				return (false);
			}
		}
	}
	if (!ft_handler_additonal_worker_pipes(root))
		return (false);
	return (true);
}
