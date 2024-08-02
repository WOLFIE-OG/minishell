/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:48:10 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 18:16:36 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_is_builtin(t_root *root, char *cmd)
{
	if (ft_is_in_strarray(root->builtin_array, cmd))
		return (true);
	else
		return (false);
}

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
	char		**dir_paths;
	char		*path;
	char		*part_paths;
	t_env_var	*var;
	int			i;

	if (ft_is_path_valid(cmd, true, false))
		return (ft_strdup(cmd));
	var = ft_get_var(root, "PATH");
	dir_paths = ft_split(var->value, ':');
	i = -1;
	while (dir_paths[++i])
	{
		part_paths = ft_strjoin(dir_paths[i], "/");
		path = ft_strjoin(part_paths, cmd);
		free(part_paths);
		if (ft_is_path_valid(path, true, false))
		{
			ft_gc_str_array(dir_paths);
			return (path);
		}
		free(path);
	}
	ft_gc_str_array(dir_paths);
	return (NULL);
}

bool	ft_is_path_valid(char *path, bool check_exec, bool check_read)
{
	if (access(path, F_OK) != 0)
		return (false);
	if (check_read && access(path, R_OK) != 0)
		return (false);
	if (check_exec && access(path, X_OK) != 0)
		return (false);
	return (true);
}
