/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/07/25 17:08:49 by otodd            ###   ########.fr       */
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

static bool	ft_handler_additonal_worker_pipes(t_root *root)
{
	if (close(root->current_cmd->io_out[0]) == -1)
	{
		perror("Error closing io_out[0]");
		return (false);
	}
	if (dup2(root->current_cmd->io_out[1], STDOUT_FILENO) == -1)
	{
		perror("Error duplicating io_out[1] to STDIN");
		return (false);
	}
	if (close(root->current_cmd->io_out[1]) == -1)
	{
		perror("Error closing io_out[1]");
		return (false);
	}
	return (true);
}

bool	ft_handle_worker_pipes(t_root *root)
{
	if (root->last_executed_cmd)
	{
		if (root->last_executed_cmd->post_action == PIPE)
		{
			if (dup2(root->last_executed_cmd->io_out[0], STDIN_FILENO) == -1)
			{
				perror("Error duplicating last io_out[0] to STDIN");
				return (false);
			}
			if (close(root->last_executed_cmd->io_out[0]) == -1)
			{
				perror("Error closing last io_out[0]");
				return (false);
			}
		}
	}
	if (!ft_handler_additonal_worker_pipes(root))
		return (false);
	return (true);
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
			break;
		arr = ft_strarrayappend2(arr, ft_strdup(line));
		free(line);
	}
	line = ft_strarraytostr(arr);
	ft_gc_str_array(arr);
	return (line);
}