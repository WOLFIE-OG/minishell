/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 14:33:53 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_executor_file_handler(t_cmd **current_cmd)
{
	if ((*current_cmd)->is_file && !(*current_cmd)->next
		&& !(*current_cmd)->prev)
	{
		if (!ft_create_file((*current_cmd)->cmd_tokens->str))
		{
			if (errno == EISDIR)
				(*current_cmd)->root->prev_cmd_status = EXIT_FAILURE;
			return (false);
		}
	}
	while ((*current_cmd)->next && (*current_cmd)->next->is_file)
	{
		*current_cmd = (*current_cmd)->next;
		(*current_cmd)->skip = true;
		if (!ft_create_file((*current_cmd)->cmd_tokens->str))
		{
			if (errno == EISDIR)
				(*current_cmd)->root->prev_cmd_status = EXIT_FAILURE;
			return (false);
		}
	}
	return (true);
}

static bool	ft_executor_input_check(t_root *root)
{
	t_cmd	*current_cmd;

	current_cmd = root->current_cmd;
	if (current_cmd->post_action == INPUT
		|| current_cmd->post_action == HEREDOC)
	{
		if (!ft_cmd_input(current_cmd, current_cmd->cmd_tokens->str))
		{
			current_cmd->skip = true;
			current_cmd->root->prev_cmd_status = EXIT_FAILURE;
		}
		close(current_cmd->pipe[1]);
		root->prev_cmd = current_cmd;
	}
	else if ((current_cmd->post_action == TRUNC
			|| current_cmd->post_action == APPEND))
	{
		if (!ft_executor_file_handler(&current_cmd))
			return (false);
		ft_cmd_trunc_append(root->current_cmd, current_cmd);
	}
	return (true);
}

static void	ft_executor_wait_forpid(t_root *root)
{
	t_cmd	*head;
	int		ret_code;

	ret_code = 0;
	head = root->prev_cmd;
	while (head)
	{
		if (head->pid != 0)
		{
			waitpid(head->pid, &ret_code, 0);
			root->prev_cmd_status_signaled = false;
			if (WIFEXITED(ret_code))
				root->prev_cmd_status = WEXITSTATUS(ret_code);
			else if (WIFSIGNALED(ret_code))
			{
				root->prev_cmd_status = WTERMSIG(ret_code);
				root->prev_cmd_status_signaled = true;
			}
			if (root->prev_cmd_status != EXIT_SUCCESS)
				ft_worker_error_print(root);
		}
		head = head->prev;
	}
}

void	ft_executor(t_root *root)
{
	root->current_cmd = root->preped_cmds;
	while (root->current_cmd)
	{
		if (root->current_cmd->skip)
		{
			root->current_cmd = root->current_cmd->next;
			continue ;
		}
		if (!ft_executor_input_check(root))
			break ;
		if (root->current_cmd->execute)
		{
			if (root->current_cmd->is_builtin)
				ft_builtins(root);
			else
				if (ft_strlen(root->current_cmd->cmd_tokens->str))
					ft_worker_launcher(root);
		}
		root->current_cmd = root->current_cmd->next;
	}
	ft_executor_wait_forpid(root);
	ft_gc_preped_cmds(root);
	root->prev_cmd = NULL;
	return ;
}
