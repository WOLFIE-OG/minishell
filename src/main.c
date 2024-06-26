/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/26 13:04:55 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_var_signal;

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	config_siginit();
	root->env = init_env(env);
}

static char	*set_prompt(t_root *root)
{
	root->prompt = ft_strarrayappend2(NULL,
			ft_strdup(get_var(root, "USER")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("@"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("minishell:"));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(get_var(root, "PWD")->value));
	return (ft_strarraytostr(root->prompt));
}

int main(int ac, char **av, char **env)
{
	char	*input;
	char	*tmp;
	t_root	root;

	g_var_signal = 0;
	ft_init_shell(&root, ac, av, env);
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
			printf("\nBye Bye Minishell\n");
			break ;
		}
		cd(&root, "/home/wolfie");
		pwd(&root);
		export(&root, "TESTVAR=test");
		add_history(input);
		free(input);
	}
	free_env_list(&root);
	exit(EXIT_SUCCESS);
}