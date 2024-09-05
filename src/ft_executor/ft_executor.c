/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/09/05 23:23:58 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_executor_input_check(t_root *root)
{
	char	*data;

	if (root->current_cmd->post_action == INPUT)
	{
		data = ft_read_from_file(root->current_cmd->cmd_tokens->str);
		if (data)
		{
			ft_putstr_fd(data, root->current_cmd->pipe[1]);
			free(data);
		}
		close(root->current_cmd->pipe[1]);
		root->prev_cmd = root->current_cmd;
	}
	else if (root->current_cmd->post_action == HEREDOC)
	{
		ft_putstr_fd(root->current_cmd->cmd_tokens->str,
			root->current_cmd->pipe[1]);
		close(root->current_cmd->pipe[1]);
		root->prev_cmd = root->current_cmd;
	}
}

static void	ft_executor_post_exec_helper(t_cmd **current_cmd)
{
	while ((*current_cmd)->next
		&& ((*current_cmd)->next->post_action == APPEND
			|| (*current_cmd)->next->post_action == TRUNC))
	{
		*current_cmd = (*current_cmd)->next;
		ft_create_file((*current_cmd)->cmd_tokens->str);
	}
	if ((*current_cmd)->next
		&& ((*current_cmd)->next->post_action == EMPTY
			|| (*current_cmd)->next->post_action == END))
		*current_cmd = (*current_cmd)->next;
}

static void	ft_executor_post_exec(t_root *root)
{
	t_cmd	*current_cmd;

	current_cmd = root->prev_cmd;
	if (current_cmd)
	{
		if (current_cmd->post_action == TRUNC
			|| current_cmd->post_action == APPEND)
		{
			if (current_cmd->next
				&& (current_cmd->next->post_action != APPEND
					&& current_cmd->next->post_action != TRUNC))
			{
				root->current_cmd = root->current_cmd->next;
				ft_cmd_trunc_append(root);
			}
			else
			{
				ft_executor_post_exec_helper(&current_cmd);
				root->prev_cmd->post_action = current_cmd->prev->post_action;
				root->current_cmd = current_cmd;
				ft_cmd_trunc_append(root);
			}
		}
	}
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
		ft_executor_input_check(root);
		if (root->current_cmd->execute)
		{
			if (root->current_cmd->is_builtin)
				ft_builtins(root);
			else
				ft_worker_launcher(root);
		}
		ft_executor_post_exec(root);
		root->current_cmd = root->current_cmd->next;
	}
	ft_executor_wait_forpid(root);
	ft_gc_preped_cmds(root);
	root->prev_cmd = NULL;
	return ;
}
