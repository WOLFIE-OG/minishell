/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/15 21:30:23 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int gvar_signal;

void    ft_init_shell(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    //what to do with env?
    config_siginit();
    //init data below
}

int main(int ac, char **av, char **env)
{
    gvar_signal = 0;
    char    *input;
    ft_init_shell(ac, av, env); //signal handling

    while(1)
    {
        char *input;
        //display prompt and read inpit
        input = readline("minishell$> "); //prompt
        add_history(input);
        config_siginit();
        if (!input)
        {
            printf("\nBye Bye Minishell\n")
            break ; //handle eof (ctrlD)
        }
    }
}