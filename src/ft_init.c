/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:28:07 by otodd             #+#    #+#             */
/*   Updated: 2024/08/20 18:09:56 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_create_builtin_array(t_root *root)
{
	root->builtin_array = ft_strarrayappend2(NULL,
			ft_strdup("cd"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("pwd"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("export"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("unset"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("env"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("exit"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("echo"));
}

static void	ft_interactive_check(t_root *root)
{
	char	**tmp;

	tmp = NULL;
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
		}
	}
}

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
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
	ft_interactive_check(root);
	ft_set_var(root, "SHELL",
		ft_strjoin(ft_get_var(root, "PWD")->value, "/minishell"));
	ft_create_builtin_array(root);
}
