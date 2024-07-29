/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/07/30 00:54:41 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_builtins(t_root *root)
{
	static int	ret = EXIT_SUCCESS;
	int			og_fd;
	char		*cmd;

	og_fd = dup(STDOUT_FILENO);
	dup2(root->current_cmd->pipe[1], STDOUT_FILENO);
	close(root->current_cmd->pipe[1]);
	cmd = root->tokens->str;
	if (!ft_strcmp(cmd, "cd"))
		ret = ft_cd(root);
	else if (!ft_strcmp(cmd, "export"))
		ret = ft_export(root);
	else if (!ft_strcmp(cmd, "env"))
		ret = ft_env(root);
	else if (!ft_strcmp(cmd, "unset"))
		ret = ft_unset(root);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(root, ret);
	else if (!ft_strcmp(cmd, "echo"))
		ret = ft_echo(root);
	else if (!ft_strcmp(cmd, "pwd"))
		ret = ft_pwd(root);
	dup2(og_fd, STDOUT_FILENO);
	close(og_fd);
	root->last_executed_cmd = root->current_cmd;
	root->current_cmd = root->current_cmd->next;
	return (ret);
}

bool	ft_exec(t_root *root)
{
	char	*cmd;
	char	**args;

	args = ft_exec_arg_str(root);
	cmd = ft_cmd_path(root, root->current_cmd->cmd_tokens->str);
	if (cmd)
	{
		if (ft_worker(root, cmd, args))
		{
			ft_gc_str_array(args);
			free(cmd);
			return (false);
		}
		free(cmd);
	}
	else
	{
		printf("no such command: %s\n", root->current_cmd->cmd_tokens->str);
		ft_gc_str_array(args);
		return (false);
	}
	ft_gc_str_array(args);
	return (true);
}

int	ft_worker(t_root *root, char *cmd, char **args)
{
	pid_t		child;
	int			ret_code;
	char		**env;

	child = fork();
	ret_code = 0;
	if (child == 0)
	{
		ft_config_sigint_cmd();
		if (!ft_handle_worker_pipes(root))
			exit(EXIT_FAILURE);
		env = ft_env_to_array(root);
		if (execve(cmd, args, env) == -1)
		{
			perror(cmd);
			ft_gc_str_array(env);
		}
	}
	else
	{
		close(root->current_cmd->pipe[1]);
		if (root->current_cmd->post_action == EMPTY
			|| root->current_cmd->post_action == END)
			ft_print_pipe_output(root->current_cmd->pipe[0]);
		wait(&ret_code);
		root->last_executed_cmd = root->current_cmd;
		root->current_cmd = root->current_cmd->next;
	}
	return (WEXITSTATUS(ret_code));
}

int	ft_executor(t_root *root, t_cmd *cmds)
{
	t_cmd	*head;

	head = cmds;
	root->current_cmd = head;
	while (head)
	{
		if (!head->cmd_tokens)
			return (EXIT_FAILURE);
		root->tokens = head->cmd_tokens;
		if (head->is_builtin)
			ft_builtins(root);
		else
			ft_exec(root);
		if (root->last_executed_cmd)
		{
			if (root->last_executed_cmd->post_action == TRUNC
				|| root->last_executed_cmd->post_action == APPEND)
			{
				head = head->next;
				ft_cmd_trunc_append(root);
			}
			else if (head->is_builtin)
				ft_cmd_output(root);
		}
		head = head->next;
	}
	root->tokens = NULL;
	root->last_executed_cmd = NULL;
	return (EXIT_SUCCESS);
}
