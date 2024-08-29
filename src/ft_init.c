/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:28:07 by otodd             #+#    #+#             */
/*   Updated: 2024/08/29 14:33:49 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_interactive_check(t_root *root)
{
	char	**tmp;

	tokenizer_tester(root->init_args_c, root->init_args);
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
	ft_interactive_check(root);
	ft_set_var(root, "SHELL",
		ft_strjoin(ft_get_var(root, "PWD")->value, "/minishell"));
}
