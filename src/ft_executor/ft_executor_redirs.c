/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:56:56 by otodd             #+#    #+#             */
/*   Updated: 2024/07/29 17:10:44 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_handler_additonal_worker_pipes(t_root *root)
{
	if (close(root->current_cmd->io_out[0]) == -1)
	{
		perror("error closing io_out[0]");
		return (false);
	}
	if (dup2(root->current_cmd->io_out[1], STDOUT_FILENO) == -1)
	{
		perror("error duplicating io_out[1] to STDIN");
		return (false);
	}
	if (close(root->current_cmd->io_out[1]) == -1)
	{
		perror("error closing io_out[1]");
		return (false);
	}
	return (true);
}

bool	ft_handle_worker_pipes(t_root *root)
{
	if (root->last_executed_cmd)
	{
		if (root->last_executed_cmd->post_action == PIPE)
		{
			if (dup2(root->last_executed_cmd->io_out[0], STDIN_FILENO) == -1)
			{
				perror("error duplicating last io_out[0] to STDIN");
				return (false);
			}
			if (close(root->last_executed_cmd->io_out[0]) == -1)
			{
				perror("error closing last io_out[0]");
				return (false);
			}
		}
	}
	if (!ft_handler_additonal_worker_pipes(root))
		return (false);
	return (true);
}
