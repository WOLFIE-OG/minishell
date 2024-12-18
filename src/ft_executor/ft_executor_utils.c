/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:48:10 by otodd             #+#    #+#             */
/*   Updated: 2024/10/30 17:37:57 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_worker_arg_str(t_root *root)
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

char	*ft_cmd_path(t_root *root, char *cmd)
{
	t_cmd_path	vars;

	vars.var = ft_get_var(root, "PATH");
	if (!vars.var)
	{
		errno = ENOENT;
		return (NULL);
	}
	vars.dir_paths = ft_split(vars.var->value, ':');
	vars.dir_paths_head = vars.dir_paths;
	while (*vars.dir_paths)
	{
		vars.part_paths = ft_strjoin(*vars.dir_paths, "/");
		vars.path = ft_strjoin(vars.part_paths, cmd);
		free(vars.part_paths);
		if (ft_is_path_valid(vars.path, true, false, false))
		{
			ft_gc_str_array(vars.dir_paths_head);
			return (vars.path);
		}
		free(vars.path);
		vars.dir_paths++;
	}
	ft_gc_str_array(vars.dir_paths_head);
	return (NULL);
}

bool	ft_is_path_binary(char *path)
{
	char	*start;
	int		len;

	len = ft_strlen(path);
	start = ft_strrchr(path, '/');
	if (start)
	{
		if (path[len] == *start)
			return (false);
		else
			return (true);
	}
	return (false);
}

bool	ft_is_path_valid(char *path, bool check_exec, bool check_read,
	bool check_write)
{
	if (access(path, F_OK) != 0)
		return (false);
	if (check_read && access(path, R_OK) != 0)
		return (false);
	if (check_write && access(path, W_OK) != 0)
		return (false);
	if (check_exec && access(path, X_OK) != 0)
		return (false);
	return (true);
}
