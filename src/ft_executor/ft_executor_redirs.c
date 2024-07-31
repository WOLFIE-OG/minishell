/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:56:56 by otodd             #+#    #+#             */
/*   Updated: 2024/07/31 17:53:47 by otodd            ###   ########.fr       */
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
	if (root->prev_cmd)
	{
		if (root->prev_cmd->post_action == PIPE
			|| root->prev_cmd->post_action == INPUT)
		{
			if (dup2(root->prev_cmd->pipe[0], STDIN_FILENO) == -1)
			{
				perror("error duplicating last pipe[0] to STDIN");
				return (false);
			}
			if (close(root->prev_cmd->pipe[0]) == -1)
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
