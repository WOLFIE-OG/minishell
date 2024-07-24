/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/07/24 22:28:25 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	ft_is_builtin(t_root *root, char *cmd)
{
	if (ft_is_in_strarray(root->builtin_array, cmd))
		return (true);
	else
		return (false);
}

static int	ft_builtins(t_root *root)
{
	static int	ret = EXIT_SUCCESS;
	int 		og_fd;
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

static void	ft_worker(t_root *root, char *cmd, char **args)
{
	pid_t		child;
	char		**env;

	child = fork();
	if (child == 0)
	{
		ft_config_sigquit();
		env = ft_env_to_array(root);
		if (root->last_executed_cmd)
		{
			close(root->last_executed_cmd->io_out[1]);
			dup2(root->last_executed_cmd->io_out[0], STDIN_FILENO);
			close(root->last_executed_cmd->io_out[0]);
		}
		close(root->current_cmd->io_out[0]);
		dup2(root->current_cmd->io_out[1], STDOUT_FILENO);
		close(root->current_cmd->io_out[1]);
		if (execve(cmd, args, env) == -1)
			printf("%s\n", "error in execve");
		ft_free_array(env, ft_strarraylen(env));
		free(env);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		close(root->current_cmd->io_out[1]);
		root->last_executed_cmd = root->current_cmd;
		root->current_cmd = root->current_cmd->next;
	}
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
			ft_free_array(dir_paths, ft_strarraylen(dir_paths));
			free(dir_paths);
			return (path);
		}
		free(path);
	}
	ft_free_array(dir_paths, ft_strarraylen(dir_paths));
	free(dir_paths);
	return (NULL);
}

static int	ft_exec(t_root *root)
{
	char	*cmd;
	char	**tmp;
	t_token	*head;

	tmp = NULL;
	head = root->current_cmd->cmd_tokens;
	cmd = ft_cmd_path(root, head->str);
	while (head)
	{
		tmp = ft_strarrayappend2(tmp, ft_strdup(head->str));
		head = head->next;
	}
	if (cmd)
	{
		ft_worker(root, cmd, tmp);
		free(cmd);
	}
	else
		printf("minishell: No Such Command: \n");
	if (tmp)
	{
		ft_free_array(tmp, ft_strarraylen(tmp));
		free(tmp);
	}
	return (EXIT_SUCCESS);
}

int	ft_executor(t_root *root, t_cmd *cmds)
{
	t_cmd	*head;
	char	*line;

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
	}
	if (root->last_executed_cmd)
		while ((line = ft_get_next_line(root->last_executed_cmd->io_out[0])))
		{
			printf("%s", line);
			free(line);
		}
	return (EXIT_FAILURE);
}
