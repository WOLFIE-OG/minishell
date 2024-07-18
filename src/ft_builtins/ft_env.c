/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:57:17 by otodd             #+#    #+#             */
/*   Updated: 2024/07/18 16:56:45 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_var(void *v)
{
	t_env_var	*var;

	var = (t_env_var *)v;
	ft_fprintf(STDOUT_FILENO, "%s=%s\n", var->key, var->value);
}

int	ft_env(t_root *root)
{
	ft_lstiter(root->env, ft_print_var);
	return (EXIT_SUCCESS);
}
