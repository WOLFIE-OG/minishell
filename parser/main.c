/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/10 11:58:22 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int gvar_signal;

int main(int ac, char **av, char **env)
{
    ft_init_shell(ac, av, env); //signal handling
    while(1)
    {
        char *input;
        //display prompt and read inpit
        input = readline("minishell$> "); //prompt
        if (!input)
        {
            //handle eof (ctrlD)
            
        }

    }
}