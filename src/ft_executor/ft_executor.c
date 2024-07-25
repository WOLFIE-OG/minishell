/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/07/25 17:18:13 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_builtins(t_root *root)
{
	static int	ret = EXIT_SUCCESS;
	int			og_fd;
	char		*cmd;

	og_fd = dup(STDOUT_FILENO);
	dup2(root->current_cmd->io_out[1], STDOUT_FILENO);
	close(root->current_cmd->io_out[1]);
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

static int	ft_worker(t_root *root, char *cmd, char **args)
{
	pid_t		child;
	int			ret_code;
	char		**env;

	child = fork();
	if (child == 0)
	{
		ft_config_sigquit();
		if (!ft_handle_worker_pipes(root))
			exit(EXIT_FAILURE);
		env = ft_env_to_array(root);
		if (execve(cmd, args, env) == -1)
		{
			perror("error in execve");
			ft_gc_str_array(env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&ret_code);
		close(root->current_cmd->io_out[1]);
		root->last_executed_cmd = root->current_cmd;
		root->current_cmd = root->current_cmd->next;
	}
	return (WEXITSTATUS(ret_code));
}

static char	*ft_cmd_path(t_root *root, char *cmd)
{
	char		**dir_paths;
	char		*path;
	char		*part_paths;
	t_env_var	*var;
	int			i;

	var = ft_get_var(root, "PATH");
	dir_paths = ft_split(var->value, ':');
	i = -1;
	while (dir_paths[++i])
	{
		part_paths = ft_strjoin(dir_paths[i], "/");
		path = ft_strjoin(part_paths, cmd);
		free(part_paths);
		if (access(path, F_OK) == 0)
		{
			ft_gc_str_array(dir_paths);
			return (path);
		}
		free(path);
	}
	ft_gc_str_array(dir_paths);
	return (NULL);
}

static char	**ft_exec_arg_str(t_root *root)
{
	char	**arg;
	t_token	*head;

	arg = NULL;
	head = root->current_cmd->cmd_tokens;
	while (head)
	{
		arg = ft_strarrayappend2(arg, ft_strdup(head->str));
		head = head->next;
	}
	return (arg);
}

static int	ft_exec(t_root *root)
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
			return (EXIT_FAILURE);
		}
		free(cmd);
	}
	else
		printf("minishell: No Such Command: \n");
	ft_gc_str_array(args);
	return (EXIT_SUCCESS);
}

int	ft_executor(t_root *root, t_cmd *cmds)
{
	t_cmd	*head;
	char	*result;

	head = cmds;
	root->current_cmd = head;
	while (head)
	{
		if (!root->current_cmd->cmd_tokens)
			return (EXIT_FAILURE);
		root->tokens = head->cmd_tokens;
		if (ft_is_builtin(root, root->current_cmd->cmd_tokens->str))
			ft_builtins(root);
		else
			ft_exec(root);
		head = head->next;
		if (root->last_executed_cmd)
		{
			if (root->last_executed_cmd->post_action != PIPE)
			{
				result = ft_build_pipe_output(root->last_executed_cmd->io_out[0]);
				if (result)
				{
					ft_putstr(result);
					free(result);
				}
			}
		}
	}
	root->last_executed_cmd = NULL;
	return (EXIT_SUCCESS);
}
