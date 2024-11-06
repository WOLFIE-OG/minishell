/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/11/06 14:26:08 by otodd            ###   ########.fr       */
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
			if (errno == EISDIR || errno == EACCES)
				(*current_cmd)->exit_code = EXIT_FAILURE;
			return (false);
		}
	}
	while ((*current_cmd)->next && (*current_cmd)->next->is_file)
	{
		*current_cmd = (*current_cmd)->next;
		(*current_cmd)->skip = true;
		if (!ft_create_file((*current_cmd)->cmd_tokens->str))
		{
			if (errno == EISDIR || errno == EACCES)
				(*current_cmd)->exit_code = EXIT_FAILURE;
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
		root->prev_cmd = current_cmd;
		if (!ft_cmd_input(current_cmd, current_cmd->cmd_tokens->str))
		{
			if (root->prev_cmd->next)
				root->prev_cmd->next->execute = false;
		}
		close(current_cmd->pipe[1]);
	}
	else if ((current_cmd->post_action == TRUNC
			|| current_cmd->post_action == APPEND))
	{
		if (!ft_executor_file_handler(&current_cmd))
		{
			root->prev_cmd = current_cmd;
			return (false);
		}
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
			if (WIFEXITED(ret_code))
				head->exit_code = WEXITSTATUS(ret_code);
			else if (WIFSIGNALED(ret_code))
			{
				head->exit_code = WTERMSIG(ret_code);
				head->exit_signaled = true;
			}
			if (head->exit_code != EXIT_SUCCESS)
				ft_worker_error_print(root);
		}
		head = head->prev;
	}
}

static void	ft_post_executor(t_root *root)
{
	if (!root->exit)
		ft_executor_wait_forpid(root);
	if (root->prev_cmd)
		root->prev_cmd_status = root->prev_cmd->exit_code;
	ft_gc_preped_cmds(root);
	root->prev_cmd = NULL;
}

void	ft_executor(t_root *root)
{
	root->current_cmd = root->preped_cmds;
	while (root->current_cmd && !root->exit)
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
			if (root->current_cmd && root->current_cmd->is_builtin)
				ft_builtins(root);
			else
				ft_worker_launcher(root);
		}
		root->current_cmd = root->current_cmd->next;
	}
	ft_post_executor(root);
	return ;
}
