/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_general_gc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:59:54 by otodd             #+#    #+#             */
/*   Updated: 2024/07/25 16:32:44 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_gc_str_array(char **arr)
{
	if (arr)
	{
		ft_free_array(arr, ft_strarraylen(arr));
		free(arr);
	}
}

void	ft_gc_shell(t_root *root)
{
	ft_free_env(root);
	ft_gc_str_array(root->builtin_array);
}