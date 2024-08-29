/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_worker_launcher.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:33:11 by otodd             #+#    #+#             */
/*   Updated: 2024/08/29 17:17:07 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_is_dir(char *path)
{
	struct stat	pth;

	if (stat(path, &pth) != 0)
		return (-1);
	if (S_ISDIR(pth.st_mode))
	{
		errno = EISDIR;
		return (true);
	}
	return (false);
}

static void	ft_worker_path_check(t_root *root, char **cmd, bool *is_binary)
{
	if (ft_is_path_binary(*cmd))
	{
		if (ft_is_path_valid(*cmd, false, false, false))
		{
			if (ft_is_path_valid(*cmd, true, false, false))
			{
				if (ft_is_dir(*cmd))
				{
					*cmd = NULL;
					*is_binary = true;
				}
				else
					*cmd = ft_strdup(root->current_cmd->cmd_tokens->str);
			}
		}
		else
		{
			*cmd = NULL;
			*is_binary = true;
		}
	}
	else
		*cmd = ft_cmd_path(root, root->current_cmd->cmd_tokens->str);
}

void	ft_worker_launcher(t_root *root)
{
	char	*cmd;
	char	**args;
	bool	is_binary;

	is_binary = false;
	args = ft_worker_arg_str(root);
	cmd = root->current_cmd->cmd_tokens->str;
	ft_worker_path_check(root, &cmd, &is_binary);
	if (cmd)
		ft_worker(root, cmd, args);
	else
		ft_worker_failure(root, is_binary);
	ft_gc_str_array(args);
	free(cmd);
	return ;
}
