/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/17 17:21:50 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "env.h"

int	gvar_signal;

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_var	*var;
	//what to do with env?
	config_siginit();
	root->env = init_env(env);
	var = get_var(root, "USER");
	ft_printf("Value: %s\n", var->value);
	set_var(root, "USER", ft_strdup("This is a test"));
	ft_printf("Value: %s\n", var->value);
}

int main(int ac, char **av, char **env)
{
	char	*input;
	t_root	root;
	gvar_signal = 0;

	ft_init_shell(&root, ac, av, env); //signal handling
	//init_envps ??

	// debug env

	while(1)
	{
		//display prompt and read inpit
		input = readline("minishell$> "); //prompt
		config_siginit();
		if (!input)
		{
			printf("\nBye Bye Minishell\n");
			break; //handle eof (ctrlD)
		}
		add_history(input);
		free(input);

	}
}