/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/11/06 02:01:23 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_builtins_execute(t_root *root)
{
	char	*cmd;

	cmd = root->current_cmd->cmd_tokens->str;
	if (!ft_strcmp(cmd, "cd"))
		root->current_cmd->exit_code = ft_cd(root);
	else if (!ft_strcmp(cmd, "export"))
		root->current_cmd->exit_code = ft_export(root);
	else if (!ft_strcmp(cmd, "env"))
		root->current_cmd->exit_code = ft_env(root->current_cmd, false);
	else if (!ft_strcmp(cmd, "unset"))
		root->current_cmd->exit_code = ft_unset(root);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(root);
	else if (!ft_strcmp(cmd, "echo"))
		root->current_cmd->exit_code = ft_echo(root->current_cmd);
	else if (!ft_strcmp(cmd, "pwd"))
		root->current_cmd->exit_code = ft_pwd(root);
}

static void	ft_builtins_handle_redir(t_root *root, int *fd)
{
	*fd = dup(STDOUT_FILENO);
	dup2(root->current_cmd->pipe[1], STDOUT_FILENO);
	close(root->current_cmd->pipe[1]);
}

static void	ft_builtins_handle_unredir(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_builtins(t_root *root)
{
	static int	fd = STDOUT_FILENO;

	if (root->current_cmd->next
		|| (root->current_cmd->next
			&& root->current_cmd->next->post_action != EMPTY))
		ft_builtins_handle_redir(root, &fd);
	ft_builtins_execute(root);
	if (root->current_cmd->next
		|| (root->current_cmd->next
			&& root->current_cmd->next->post_action != EMPTY))
		ft_builtins_handle_unredir(fd);
	root->prev_cmd = root->current_cmd;
}
