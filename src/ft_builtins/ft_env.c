/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:57:17 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 17:07:24 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_var(void *v)
{
	t_env_var	*var;

	var = (t_env_var *)v;
	printf("%s=%s\n", var->key, var->value);
}

void	ft_env(t_root *root)
{
	ft_lstiter(root->env, ft_print_var);
}
