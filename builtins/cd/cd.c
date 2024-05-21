/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/05/21 15:33:17 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"

// void	cd(char **data)
// {
// 
// }

int	main(int arg_n, char **arg_a, char *env[])
{
	char cwd[256];

	(void)arg_n;
	// cd(arg_a);

	// chdir("/home/wolfie/.ssh");
	ft_printf("Path: %s", getcwd(cwd, sizeof(cwd)));
	return (EXIT_SUCCESS);
}
