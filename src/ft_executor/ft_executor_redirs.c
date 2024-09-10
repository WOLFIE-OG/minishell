/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:56:56 by otodd             #+#    #+#             */
/*   Updated: 2024/09/09 19:53:05 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_close_pipes(t_root *root)
{
	t_cmd	*head;

	head = root->preped_cmds;
	while (head)
	{
		close(head->pipe[0]);
		close(head->pipe[1]);
		head = head->next;
	}
}

static bool	ft_handler_additonal_worker_pipes(t_root *root)
{
	if (root->current_cmd->next)
	{
		if (root->current_cmd->post_action == PIPE
			|| root->current_cmd->post_action == APPEND
			|| root->current_cmd->post_action == TRUNC)
		{
			if (dup2(root->current_cmd->pipe[1], STDOUT_FILENO) == -1)
			{
				perror("pipe[1]: Error duplicating to STDOUT: ");
				return (false);
			}
			close(root->current_cmd->pipe[1]);
			close(root->current_cmd->pipe[0]);
		}
	}
	return (true);
}

bool	ft_handle_worker_pipes(t_root *root)
{
	if (root->prev_cmd)
	{
		if (root->prev_cmd->post_action == PIPE
			|| root->prev_cmd->post_action == INPUT
			|| root->prev_cmd->post_action == HEREDOC)
		{
			if (dup2(root->prev_cmd->pipe[0], STDIN_FILENO) == -1)
			{
				perror("pipe[0]: Error duplicating to STDIN: ");
				return (false);
			}
			close(root->prev_cmd->pipe[0]);
			close(root->prev_cmd->pipe[1]);
		}
	}
	if (!ft_handler_additonal_worker_pipes(root))
		return (false);
	ft_close_pipes(root);
	return (true);
}
