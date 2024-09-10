/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/09/09 18:12:40 by otodd            ###   ########.fr       */
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

void	ft_cmd_trunc_append(t_cmd *cmd, char *path)
{
	bool	append;

	if (!ft_is_path_valid(path, false, false, true))
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", strerror(errno), path);
		return ;
	}
	append = false;
	if (cmd->post_action == APPEND)
		append = true;
	close(cmd->pipe[1]);
	cmd->pipe[1] = ft_file_fd(append, false, path);
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


int	ft_file_fd(bool append, bool input, char *path)
{
	int	fd;
	int	perms;

	if (!input)
	{
		perms = O_WRONLY | O_CREAT;
		if (append)
			perms = perms | O_APPEND;
		else
			perms = perms | O_TRUNC;
	}
	else
		perms = O_RDONLY;
	fd = open(path, perms, 0777);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (fd);
}

void	ft_cmd_input(t_cmd *cmd, char *path)
{
	if (!ft_is_path_valid(path, false, true, false))
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", strerror(errno), path);
		return ;
	}
	close(cmd->pipe[0]);
	cmd->pipe[0] = ft_file_fd(false, true, path);
	close(cmd->pipe[1]);
}
