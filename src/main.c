/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/02 17:00:11 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_var_signal;

static void	create_builtin_array(t_root *root)
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
	(void)av;
	config_siginit();
	root->env = init_env(env);
	create_builtin_array(root);
}

static char	*set_prompt(t_root *root)
{
	root->prompt = ft_strarrayappend2(NULL, ft_strdup(BGRN));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(get_var(root, "USER")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("@"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("minishell:"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(BBLU));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(get_var(root, "PWD")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("$ "));
	return (ft_strarraytostr(root->prompt));
}

static void	builtin_test(t_root *root)
{
	char	**tmp;
	ft_cd(root, "~/");
	ft_export(root, "TESTVAR=test");
	tmp = ft_strarrayappend2(NULL, ft_strdup("/bin/ls"));
	tmp = ft_strarrayappend2(tmp, ft_strdup(get_var(root, "HOME")->value));
	tmp = ft_strarrayappend2(tmp, ft_strdup("-la"));
	runner_process(root, tmp);
	ft_free_array(tmp, ft_strarraylen(tmp));
	free(tmp);
	//ft_echo(ft_strarrayappend2(ft_strarrayappend2(NULL,
	// 	"/usr/bin"), get_var(root, "PWD")->value));
	// printf("%d\n", is_builtin(root, "cd"));
	// ft_pwd(root);
	// ft_unset(root, "TESTVAR");
	// ft_env(root);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*tmp;
	t_root	root;

	g_var_signal = 0;
	ft_init_shell(&root, ac, av, envp);
	while (true)
	{
		tmp = set_prompt(&root);
		input = readline(tmp);
		ft_free_array(root.prompt, ft_strarraylen(root.prompt));
		free(root.prompt);
		free(tmp);
		config_siginit();
		if (!input)
		{
			printf("Bye Bye Minishell\n");
			break ;
		}
		builtin_test(&root);
		add_history(input);
		free(input);
	}
	kill_shell(&root, EXIT_SUCCESS);
}
