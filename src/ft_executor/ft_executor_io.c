/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/07/30 21:47:41 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cmd_output(t_root *root)
{
	char	*result;

	result = ft_fd_to_str(root->current_cmd->pipe[0]);
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

	root->current_cmd = root->current_cmd->next;
	append = false;
	if (root->last_executed_cmd->post_action == APPEND)
		append = true;
	result = ft_fd_to_str(root->last_executed_cmd->pipe[0]);
	if (!ft_write_to_file(result, append, root->current_cmd->cmd_tokens->str))
		perror("permission denied");
	free(result);
	root->last_executed_cmd = root->current_cmd;
}

char	*ft_fd_to_str(int fd)
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

void	ft_print_pipe_output(int fd)
{
	char	*line;

	while (true)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		ft_putstr(line);
		free(line);
	}
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

char	*ft_read_from_file(char *path)
{
	int		fd;
	char	*data;

	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
		return (NULL);
	data = ft_fd_to_str(fd);
	close(fd);
	return (data);
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
