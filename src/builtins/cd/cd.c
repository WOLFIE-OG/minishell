/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/06/25 14:12:01 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cd(t_root *root, char *path)
{
	t_env_var	*_pwd;
	char		*pth;

	if (path[(ft_strlen(path) - 1)] == '/')
		pth = ft_strndup(path, (ft_strlen(path) - 1));
	else
		pth = ft_strdup(path);
	_pwd = get_var(root, "PWD");
	if (!chdir(path))
	{
		set_var(root, "OLDPWD", ft_strdup(_pwd->value));
		set_var(root, "PWD", pth);
	}
}
