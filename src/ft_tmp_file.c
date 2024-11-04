/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:46:56 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/04 16:22:49 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_generate_tmp_file(char *tmp, int lvl)
{
	char	*tmp_name;
	char	*n;
	char	*path;

	n = ft_itoa(lvl);
	tmp_name = ft_strjoin(tmp, n);
	free(n);
	path = ft_strjoin("/tmp/", tmp_name);
	free(tmp_name);
	return (path);
}

static void	ft_tmp_file_loop(char *tmp, char **path)
{
	int		lvl;

	*path = NULL;
	lvl = 0;
	while (true)
	{
		*path = ft_generate_tmp_file(tmp, lvl);
		if (!ft_is_path_valid(*path, false, false, false))
			break ;
		free(path);
		lvl++;
	}
}

char	*ft_write_to_tmp(char *tmp, char *data, bool set_fd, int pipe_fd)
{
	int		fd;
	char	*path;

	ft_tmp_file_loop(tmp, &path);
	if (!ft_create_file(path))
	{
		free(path);
		return (NULL);
	}
	fd = ft_file_fd(false, false, path);
	ft_putstr_fd(data, fd);
	close(fd);
	if (set_fd)
	{
		fd = ft_file_fd(false, true, path);
		if (dup2(fd, pipe_fd) == -1)
		{
			ft_fprintf(STDERR_FILENO, "error duping fd: %d -> %d: %s\n",
				fd, pipe_fd, strerror(errno));
			close(fd);
			free(path);
			return (NULL);
		}
	}
	return (path);
}
