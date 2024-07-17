/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/17 01:58:28 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_root *root)
{
	t_env_var	*var;
	t_token		*arg;
	char		*pth;
	int			r_code;
	char		cwd[4096];

	arg = ft_find_token_by_index(root, 1);
	if (!arg)
	{
		var = ft_get_var(root, "HOME");
		pth = ft_strdup(var->value);
	}
	else
	{
		if (!ft_strlen(arg->str) || !ft_strcmp(arg->str, "~/"))
		{
			var = ft_get_var(root, "HOME");
			arg->str = var->value;
		}
		else if (!ft_strcmp(arg->str, "-"))
			var = ft_get_var(root, "OLDPWD");
		else
			var = ft_get_var(root, "PWD");
		if (arg->str[(ft_strlen(arg->str) - 1)] == '/')
			pth = ft_strndup(arg->str, (ft_strlen(arg->str) - 1));
		else
			pth = ft_strdup(arg->str);
	}
	r_code = chdir(pth);
	if (r_code != 0)
	{
		free(pth);
		return (r_code);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		free(pth);
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	ft_set_var(root, "OLDPWD", ft_strdup(var->value));
	ft_set_var(root, "PWD", ft_strdup(cwd));
	free(pth);
	return (EXIT_SUCCESS);
}
