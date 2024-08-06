/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/08/06 17:22:37 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_worker_handle_child(t_root *root, char *cmd, char **args)
{
	char	**env;

	if (!ft_handle_worker_pipes(root))
		exit(EXIT_FAILURE);
	env = ft_env_to_array(root);
	if (execve(cmd, args, env) == -1)
	{
		perror(cmd);
		ft_gc_str_array(env);
	}
}

static void	ft_worker_handle_parent(t_root *root, pid_t pid, int *ret_code)
{
	close(root->current_cmd->pipe[1]);
	if (root->current_cmd->post_action == EMPTY
		|| root->current_cmd->post_action == END)
		ft_cmd_output(root);
	waitpid(pid, ret_code, 0);
	root->prev_cmd = root->current_cmd;
}

void	ft_worker(t_root *root, char *cmd, char **args)
{
	pid_t		child;
	int			ret_code;

	ret_code = 0;
	child = fork();
	if (child == -1)
	{
		perror("fork");
		root->prev_cmd_status = EXIT_FAILURE;
		return ;
	}
	if (child == 0)
		ft_worker_handle_child(root, cmd, args);
	else
		ft_worker_handle_parent(root, child, &ret_code);
	root->prev_cmd_status = WEXITSTATUS(ret_code);
	ft_config_sigint();
}
