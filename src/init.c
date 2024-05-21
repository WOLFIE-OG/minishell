/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/05/21 16:00:41 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int arg_n, char **arg_a, char *env[])
{
	(void)arg_n;
	(void)arg_a;
	while (*env)
	{
		// ft_printf("%a\n", ft_split(*env, '='));
		ft_printf("%s\n", *env);
		env++;
	}
	return (EXIT_SUCCESS);
}