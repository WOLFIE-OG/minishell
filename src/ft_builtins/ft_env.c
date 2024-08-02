/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:57:17 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 17:42:42 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_var(void *v)
{
	t_env_var	*var;

	var = (t_env_var *)v;
	printf("%s=%s\n", var->key, var->value);
}

int	ft_env(t_root *root)
{
	ft_lstiter(root->env, ft_print_var);
	return (EXIT_SUCCESS);
}
