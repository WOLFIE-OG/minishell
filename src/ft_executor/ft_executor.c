/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/07/18 17:34:21 by otodd            ###   ########.fr       */
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
	char		*cmd;

	if (!ft_token_size(root->tokens))
		return (ret);
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
	return (ret);
}

static void	ft_worker(t_root *root, char *cmd, char **args)
{
	pid_t		child;
	int			pipefd[2];
	char		*line;
	char		**env;

	pipe(pipefd);
	child = fork();
	ft_config_sigquit();
	if (child == 0)
	{
		env = ft_env_to_array(root);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd, args, env);
		ft_free_array(env, ft_strarraylen(env));
		free(env);
		free(cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		while ((line = ft_get_next_line(pipefd[0])))
		{
			printf("%s", line);
			free(line);
		}
		close(pipefd[0]);
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
			return (path);
		free(path);
	}
	ft_free_array(dir_paths, ft_strarraylen(dir_paths));
	free(dir_paths);
	return (NULL);
}

static void	ft_exec(t_root *root)
{
	char	*cmd;
	char	**tmp;
	t_token	*head;

	tmp = NULL;
	head = root->tokens;
	cmd = ft_cmd_path(root, head->str);
	while (head)
	{
		tmp = ft_strarrayappend2(tmp, ft_strdup(head->str));
		head = head->next;
	}
	if (cmd)
		ft_worker(root, cmd, tmp);
	else
		printf("minishell: No Such Command: \n");
	if (tmp)
	{
		ft_free_array(tmp, ft_strarraylen(tmp));
		free(tmp);
	}
}

void	ft_executor(t_root *root)
{
	if (root->tokens)
	{
		if (ft_is_builtin(root, root->tokens->str))
			ft_builtins(root);
		else
			ft_exec(root);
	}
}

