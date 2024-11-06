/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 21:20:35 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_create_file(char *path)
{
	int	fd;
	int	perms;

	perms = O_CREAT;
	fd = open(path, perms, 0644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", path, strerror(errno));
		return (false);
	}
	close(fd);
	return (true);
}

void	ft_cmd_trunc_append(t_cmd *cmd, t_cmd *cmd2)
{
	bool	append;
	int		fd;

	if (!ft_is_path_valid(cmd2->cmd_tokens->str, false, false, true))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n",
			cmd2->cmd_tokens->str, strerror(errno));
		return ;
	}
	append = false;
	if (cmd2->pre_action == APPEND)
		append = true;
	fd = ft_file_fd(append, false, cmd2->cmd_tokens->str);
	if (dup2(fd, cmd->pipe[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "error duping fd: %d -> %d: %s\n",
			fd, cmd->pipe[1], strerror(errno));
		close(fd);
		return ;
	}
	close(fd);
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
		perms = O_WRONLY;
		if (append)
			perms = perms | O_APPEND;
		else
			perms = perms | O_TRUNC;
	}
	else
		perms = O_RDONLY;
	fd = open(path, perms, 0644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", path, strerror(errno));
		return (-1);
	}
	return (fd);
}

bool	ft_cmd_input(t_cmd *cmd, char *path)
{
	int	fd;

	if (!ft_is_path_valid(path, false, true, false))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", path, strerror(errno));
		cmd->exit_code = EXIT_FAILURE;
		return (false);
	}
	fd = ft_file_fd(false, true, path);
	if (dup2(fd, cmd->pipe[0]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "error duping fd: %d -> %d: %s\n",
			fd, cmd->pipe[0], strerror(errno));
		cmd->exit_code = EXIT_FAILURE;
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
