/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/07/29 17:58:29 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cmd_output(t_root *root)
{
	char	*result;

	result = ft_build_pipe_output(root->last_executed_cmd->io_out[0]);
	if (result)
	{
		ft_putstr(result);
		free(result);
	}
}

void	ft_cmd_trunc_append(t_root *root)
{
	bool	append;
	char	*result;

	append = false;
	if (root->last_executed_cmd->post_action == APPEND)
		append = true;
	result = ft_build_pipe_output(root->last_executed_cmd->io_out[0]);
	if (!ft_write_to_file(result, append, "test.txt"))
		perror("permission denied");
	free(result);
}

char	*ft_build_pipe_output(int fd)
{
	char	*line;
	char	**arr;

	arr = NULL;
	while (true)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		arr = ft_strarrayappend2(arr, ft_strdup(line));
		free(line);
	}
	line = ft_strarraytostr(arr);
	ft_gc_str_array(arr);
	return (line);
}

bool	ft_write_to_file(char *data, bool append, char *path)
{
	int	fd;
	int	perms;

	perms = O_WRONLY | O_CREAT;
	if (append)
		perms = perms | O_APPEND;
	else
		perms = perms | O_TRUNC;
	fd = open(path, perms, 0644);
	if (fd == -1)
		return (false);
	if (data)
		ft_putstr_fd(data, fd);
	close(fd);
	return (true);
}

char	*ft_cmd_path(t_root *root, char *cmd)
{
	char		**dir_paths;
	char		*path;
	char		*part_paths;
	t_env_var	*var;
	int			i;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
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
