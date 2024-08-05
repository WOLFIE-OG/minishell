/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker_launcher.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:33:11 by otodd             #+#    #+#             */
/*   Updated: 2024/08/05 14:22:44 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_worker_exec(t_root *root, char *cmd, char **args)
{
	ft_worker(root, cmd, args);
	if (!root->prev_cmd_status)
	{
		ft_gc_str_array(args);
		free(cmd);
		return (false);
	}
	return (true);
}

static void	ft_worker_no_cmd(t_root *root, char **args)
{
	ft_fprintf(STDERR_FILENO, "minishell: command not found: %s\n",
		root->current_cmd->cmd_tokens->str);
	ft_gc_str_array(args);
	root->prev_cmd_status = EXIT_FAILURE;
}

void	ft_worker_launcher(t_root *root)
{
	char	*cmd;
	char	**args;

	args = ft_worker_arg_str(root);
	cmd = ft_cmd_path(root, root->current_cmd->cmd_tokens->str);
	if (cmd)
	{
		if (!ft_worker_exec(root, cmd, args))
			return ;
	}
	else
		return (ft_worker_no_cmd(root, args));
	ft_gc_str_array(args);
	return ;
}
