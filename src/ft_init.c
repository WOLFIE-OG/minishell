/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:28:07 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 13:09:07 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_interactive_check(t_root *root)
{
	static char	**tmp = NULL;

	if (root->init_args_c > 1)
	{
		if (root->init_args[1][0] == '-')
		{
			if (root->init_args[1][1] && root->init_args[1][1] == 'c')
			{
				root->interactive = false;
				root->init_args = &*(root->init_args + 2);
				while (*root->init_args)
				{
					tmp = ft_strarrayappend2(tmp, ft_strdup(*root->init_args));
					tmp = ft_strarrayappend2(tmp, ft_strdup(" "));
					root->init_args++;
				}
				root->interactive_str = ft_strarraytostr(tmp);
				ft_gc_str_array(tmp);
			}
			else
				ft_exit(root, EXIT_FAILURE);
		}
		else
			ft_exit(root, EXIT_FAILURE);
	}
}

static void	ft_init_vars(t_root *root)
{
	char	cwd[4096];

	if (!ft_get_var(root, "USER"))
		ft_set_var(root, "USER", ft_strdup("user"));
	if (!ft_get_var(root, "PWD"))
	{
		getcwd(cwd, sizeof(cwd));
		ft_set_var(root, "OLDPWD", ft_strdup(cwd));
		ft_set_var(root, "PWD", ft_strdup(cwd));
	}
	if (!ft_get_var(root, "HOME"))
		ft_set_var(root, "HOME",
			ft_strdup(ft_get_var(root, "PWD")->value));
}

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
	ft_config_sigint();
	root->prev_cmd = NULL;
	root->prev_cmd_status = EXIT_SUCCESS;
	root->preped_cmds = NULL;
	root->current_cmd = NULL;
	root->env = ft_init_env(env);
	root->shell_name = "minishell";
	root->interactive = true;
	root->interactive_str = NULL;
	root->init_args = av;
	root->init_args_c = ac;
	root->init_env = env;
	root->prompt = NULL;
	ft_interactive_check(root);
	ft_init_vars(root);
}
