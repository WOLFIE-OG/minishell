/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/09/04 18:08:31 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_process_arg(t_root *root, t_token *arg, t_env_var **var)
{
	if (!ft_strlen(arg->str))
	{
		*var = ft_get_var(root, "HOME");
		arg->str = (*var)->value;
	}
	else if (ft_strcmp(arg->str, "-") == 0)
	{
		free(arg->str);
		*var = ft_get_var(root, "OLDPWD");
		arg->str = ft_strdup((*var)->value);
	}
	else
		*var = ft_get_var(root, "PWD");
	if (ft_strcmp(arg->str, "/") != 0
		&& arg->str[(ft_strlen(arg->str) - 1)] == '/')
		return (ft_strndup(arg->str, (ft_strlen(arg->str) - 1)));
	else
		return (ft_strdup(arg->str));
}

static char	*ft_cd_internal(t_root *root, t_token *arg)
{
	t_env_var	*var;
	char		*pth;
	char		cwd[4096];

	if (!arg)
	{
		var = ft_get_var(root, "HOME");
		pth = ft_strdup(var->value);
	}
	else
		pth = ft_process_arg(root, arg, &var);
	if (chdir(pth) != 0)
		return (pth);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		free(pth);
		return (NULL);
	}
	ft_set_var(root, "OLDPWD", ft_strdup(var->value));
	ft_set_var(root, "PWD", ft_strdup(cwd));
	free(pth);
	return (NULL);
}

int	ft_cd(t_root *root)
{
	char	*res;
	char	*err;

	res = ft_cd_internal(root,
			ft_find_token_by_index(root->current_cmd->cmd_tokens, 1));
	if (res)
	{
		err = ft_strjoin("minishell: cd: ", res);
		perror(err);
		free(res);
		free(err);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
