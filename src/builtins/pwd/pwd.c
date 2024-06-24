/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/06/24 19:26:06 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	pwd(t_root *root)
{
	const t_env_var	*var = get_var(root, "PWD");

	printf("%s\n", var->value);
}

// int	main(int arg_n, char **arg_a)
// {
// 	char	cwd[256];
// 
// 	(void)arg_n;
// 	ft_printf("%s\n", getcwd(cwd, sizeof(cwd)));
// 	return (EXIT_SUCCESS);
// }
