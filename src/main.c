/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/24 19:25:27 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	gvar_signal;

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	// t_env_var	*var;
	// char		*temp;
	//what to do with env?
	config_siginit();
	root->env = init_env(env);
	// var = get_var(root, "OLDPWD");
	// if (var)
	// 	ft_printf("Value: %s\n", var->value);
	// temp = ft_strdup("This is a test");
	// set_var(root, "THISSSS", temp);
	// free(temp);
	// var = get_var(root, "THISSSS");
	// ft_printf("Value: %s\n", var->value);
}

int main(int ac, char **av, char **env)
{
	char	*input;
	char	*tmp;
	t_root	root;
	gvar_signal = 0;

	ft_init_shell(&root, ac, av, env); //signal handling
	//init_envps ??

	// debug env

	while(true)
	{
		//display prompt and read inpit
		root.prompt = ft_strarrayappend2(NULL, ft_strdup(get_var(&root, "USER")->value));
		root.prompt = ft_strarrayappend2(root.prompt, ft_strdup("@"));
		root.prompt = ft_strarrayappend2(root.prompt, ft_strdup("minishell:"));
		root.prompt = ft_strarrayappend2(root.prompt, ft_strdup(get_var(&root, "PWD")->value));
		tmp = ft_strarraytostr(root.prompt);
		input = readline(tmp); //prompt
		ft_free_array(root.prompt, ft_strarraylen(root.prompt));
		free(root.prompt);
		free(tmp);
		config_siginit();
		if (!input)
		{
			printf("\nBye Bye Minishell\n");
			break; //handle eof (ctrlD)
		}
		cd(&root, "/home/wolfie");
		pwd(&root);
		add_history(input);
		free(input);
	}
	free_env_list(&root);
	rl_clear_history();
	rl_free_line_state();
}