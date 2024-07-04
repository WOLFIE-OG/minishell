/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:34 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 17:11:19 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_runner_process(t_root *root, char **args)
{
	pid_t		child;
	int			pipefd[2];
	char		*line;
	char		**env;

	pipe(pipefd);
	child = fork();
	if (child == 0)
	{
		env = ft_env_to_array(root);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(args[0], args, env);
		ft_free_array(env, ft_strarraylen(env));
		free(env);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);
		while ((line = ft_get_next_line(pipefd[0])))
		{
			printf("%s", line);
			free(line);
		}
		close(pipefd[0]);
	}
}

bool	ft_is_builtin(t_root *root, char *cmd)
{
	if (ft_is_in_strarray(root->builtin_array, cmd))
		return (true);
	else
		return (false);
}
