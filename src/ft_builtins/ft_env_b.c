/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:57:17 by otodd             #+#    #+#             */
/*   Updated: 2024/10/30 18:44:45 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_write_to_tmp(char *tmp, char *data, int pipe_fd)
{
	int		fd;
	char	*path;

	path = ft_strjoin("/tmp/", tmp);
	if (!ft_create_file(path))
	{
		free(path);
		return (EXIT_FAILURE);
	}
	fd = ft_file_fd(false, false, path);
	ft_putstr_fd(data, fd);
	close(fd);
	fd = ft_file_fd(false, true, path);
	if (dup2(fd, pipe_fd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: error duping fd: %d -> %d: %s\n",
			fd, pipe_fd, strerror(errno));
		close(fd);
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	return (EXIT_SUCCESS);
}

int	ft_env(t_root *root, t_cmd *cmd, bool declare)
{
	char	*env;
	char	**env_arr;

	if (declare)
		env_arr = ft_env_to_declare_array(root);
	else
		env_arr = ft_env_to_array(root, true);
	env = ft_strarraytostr(env_arr);
	if (ft_strlen(env) > 4096 && cmd->next)
	{
		if (!ft_write_to_tmp("minishell_tmp_env_cmd", env, cmd->pipe[0]))
		{
			free(env);
			ft_gc_str_array(env_arr);
			return (EXIT_FAILURE);
		}
	}
	else
		ft_putstr(env);
	free(env);
	ft_gc_str_array(env_arr);
	return (EXIT_SUCCESS);
}
