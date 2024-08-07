/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/08/07 18:30:47 by otodd            ###   ########.fr       */
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
	if (root->prev_cmd->post_action == APPEND)
		append = true;
	result = ft_fd_to_str(root->prev_cmd->pipe[0]);
	ft_write_to_file(result, append, root->current_cmd->cmd_tokens->str);
	free(result);
	root->prev_cmd = root->current_cmd;
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

void	ft_write_to_file(char *data, bool append, char *path)
{
	int	fd;
	int	perms;

	if (!ft_is_path_valid(path, false, false, true))
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", strerror(errno), path);
		return ;
	}
	perms = O_WRONLY | O_CREAT;
	if (append)
		perms = perms | O_APPEND;
	else
		perms = perms | O_TRUNC;
	fd = open(path, perms, 0644);
	if (fd == -1)
		return ;
	if (data)
		ft_putstr_fd(data, fd);
	close(fd);
	return ;
}

char	*ft_read_from_file(char *path)
{
	int		fd;
	char	*data;

	if (!ft_is_path_valid(path, false, true, false))
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", strerror(errno), path);
		return (NULL);
	}
	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
		return (NULL);
	data = ft_fd_to_str(fd);
	close(fd);
	return (data);
}
