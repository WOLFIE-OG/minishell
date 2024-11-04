/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 17:36:17 by otodd            ###   ########.fr       */
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
	if (ft_strcmp(arg->str, "//") == 0)
		return (ft_strdup("//"));
	else
		return (ft_strdup(arg->str));
}

static bool	ft_cd_arg_check(t_token *arg)
{
	int		i;

	i = 0;
	while (arg)
	{
		i++;
		if (i > 1)
		{
			ft_print_err(ft_strdup("cd: too many arguments"));
			return (false);
		}
		arg = arg->next;
	}
	return (true);
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
	t_token	*arg;
	char	*res;
	char	*err;

	arg = ft_find_token_by_index(root->current_cmd->cmd_tokens, 1);
	if (!ft_cd_arg_check(arg))
		return (EXIT_FAILURE);
	res = ft_cd_internal(root, arg);
	if (res)
	{
		err = ft_strjoin("cd: ", res);
		perror(err);
		free(res);
		free(err);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
