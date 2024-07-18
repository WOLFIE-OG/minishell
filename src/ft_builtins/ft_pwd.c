/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/18 16:57:36 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_root *root)
{
	const t_env_var	*var = ft_get_var(root, "PWD");

	if (ft_fprintf(STDOUT_FILENO, "%s\n", var->value))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
