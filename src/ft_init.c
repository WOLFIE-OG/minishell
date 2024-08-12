/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:28:07 by otodd             #+#    #+#             */
/*   Updated: 2024/08/12 18:19:31 by otodd            ###   ########.fr       */
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

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
	(void)ac;
	root->prev_cmd = NULL;
	root->prev_cmd_status = EXIT_SUCCESS;
	root->preped_cmds = NULL;
	root->current_cmd = NULL;
	root->env = ft_init_env(env);
	root->shell_name = "minishell";
	root->init_args = *av;
	ft_set_var(root, "SHELL",
		ft_strjoin(ft_get_var(root, "PWD")->value, "/minishell"));
	ft_create_builtin_array(root);
}
