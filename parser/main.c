/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/16 13:43:05 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int gvar_signal;

void    ft_init_shell(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	//what to do with env?
	config_siginit();
	//init data below
}

int main(int ac, char **av, char **env)
{
	gvar_signal = 0;
	char    *input;
	ft_init_shell(ac, av, env); //signal handling
	//init_envps ??

	while(1)
	{
		//display prompt and read inpit
		input = readline("minishell$> "); //prompt
		config_siginit();
		if (!input)
		{
			printf("\nBye Bye Minishell\n");
			break ; //handle eof (ctrlD)
		}
		add_history(input);
		free(input);

	}
}