/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 17:07:34 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_root *root, char *path)
{
	t_env_var	*var;
	char		*pth;
	int			r_code;

	if (!ft_strlen(path) || !ft_strcmp(path, "~/"))
	{
		var = ft_get_var(root, "HOME");
		path = var->value;
	}
	else
		var = ft_get_var(root, "PWD");
	if (path[(ft_strlen(path) - 1)] == '/')
		pth = ft_strndup(path, (ft_strlen(path) - 1));
	else
		pth = ft_strdup(path);
	r_code = chdir(path);
	if (r_code != 0)
	{
		free(pth);
		return (r_code);
	}
	ft_set_var(root, "OLDPWD", ft_strdup(var->value));
	ft_set_var(root, "PWD", pth);
	return (EXIT_SUCCESS);
}
