/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/10/30 18:46:02 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_builtins_execute(t_root *root, int fd)
{
	char	*cmd;

	cmd = root->current_cmd->cmd_tokens->str;
	if (!ft_strcmp(cmd, "cd"))
		root->prev_cmd_status = ft_cd(root);
	else if (!ft_strcmp(cmd, "export"))
		root->prev_cmd_status = ft_export(root);
	else if (!ft_strcmp(cmd, "env"))
		root->prev_cmd_status = ft_env(root, root->current_cmd, false);
	else if (!ft_strcmp(cmd, "unset"))
		root->prev_cmd_status = ft_unset(root);
	else if (!ft_strcmp(cmd, "exit"))
	{
		ft_putstr("exit\n");
		if (fd != STDOUT_FILENO)
			close(fd);
		ft_exit(root, root->prev_cmd_status);
	}
	else if (!ft_strcmp(cmd, "echo"))
		root->prev_cmd_status = ft_echo(root);
	else if (!ft_strcmp(cmd, "pwd"))
		root->prev_cmd_status = ft_pwd(root);
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
	ft_builtins_execute(root, fd);
	if (root->current_cmd->next
		|| (root->current_cmd->next
			&& root->current_cmd->next->post_action != EMPTY))
		ft_builtins_handle_unredir(fd);
	root->prev_cmd = root->current_cmd;
}
