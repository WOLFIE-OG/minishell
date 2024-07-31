/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/07/31 18:34:35 by otodd            ###   ########.fr       */
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
			ft_putstr_fd(data, root->current_cmd->pipe[1]);
		close(root->current_cmd->pipe[1]);
		root->prev_cmd = root->current_cmd;
	}
}

static void	ft_executor_post_exec(t_root *root)
{
	if (root->prev_cmd)
	{
		if (root->prev_cmd->post_action == TRUNC
			|| root->prev_cmd->post_action == APPEND)
			ft_cmd_trunc_append(root);
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
	ft_gc_preped_cmds(root);
	root->prev_cmd = NULL;
	return ;
}
