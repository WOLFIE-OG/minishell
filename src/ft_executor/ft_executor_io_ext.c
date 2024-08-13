/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_io_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:31:02 by otodd             #+#    #+#             */
/*   Updated: 2024/08/13 18:37:51 by otodd            ###   ########.fr       */
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
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", strerror(errno), path);
		return (false);
	}
	close(fd);
	return (true);
}
