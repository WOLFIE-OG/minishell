/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/09/10 16:20:15 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_builtins_execute(t_root *root)
{
	char		*cmd;

	cmd = root->current_cmd->cmd_tokens->str;
	if (!ft_strcmp(cmd, "cd"))
		root->prev_cmd_status = ft_cd(root);
	else if (!ft_strcmp(cmd, "export"))
		root->prev_cmd_status = ft_export(root);
	else if (!ft_strcmp(cmd, "env"))
		root->prev_cmd_status = ft_env(root);
	else if (!ft_strcmp(cmd, "unset"))
		root->prev_cmd_status = ft_unset(root);
	else if (!ft_strcmp(cmd, "exit"))
	{
		ft_putstr("exit\n");
		ft_exit(root, root->prev_cmd_status);
	}
	else if (!ft_strcmp(cmd, "echo"))
		root->prev_cmd_status = ft_echo(root);
	else if (!ft_strcmp(cmd, "pwd"))
		root->prev_cmd_status = ft_pwd(root);
}

static void	ft_builtins_handle_redir(t_root *root, int *original_stdout_fd)
{
	*original_stdout_fd = dup(STDOUT_FILENO);
	dup2(root->current_cmd->pipe[1], STDOUT_FILENO);
	close(root->current_cmd->pipe[1]);
}

static void	ft_builtins_handle_unredir(int original_stdout_fd)
{
	dup2(original_stdout_fd, STDOUT_FILENO);
	close(original_stdout_fd);
}

void	ft_builtins(t_root *root)
{
	int			original_stdout_fd;

	if (root->current_cmd->next
		|| (root->current_cmd->next
			&& (root->current_cmd->next->post_action != EMPTY
				|| root->current_cmd->next->post_action != END)))
		ft_builtins_handle_redir(root, &original_stdout_fd);
	ft_builtins_execute(root);
	if (root->current_cmd->next
		|| (root->current_cmd->next
			&& (root->current_cmd->next->post_action != EMPTY
				|| root->current_cmd->next->post_action != END)))
		ft_builtins_handle_unredir(original_stdout_fd);
	root->prev_cmd = root->current_cmd;
}
