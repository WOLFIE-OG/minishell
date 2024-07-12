/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/12 19:30:07 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_root *root)
{
	int		arg_n;
	bool	has_flag;
	t_token	*flag;
	t_token	*arg;

	arg_n = 1;
	has_flag = false;
	flag = ft_find_token_by_index(root, 1);
	if (!flag)
		return ;
	if (ft_strrep(flag->str, 'n'))
	{
		arg_n = 2;
		has_flag = true;
	}
	arg = ft_find_token_by_index(root, arg_n);
	while (arg)
	{
		ft_putstr(arg->str);
		if (arg->next)
			ft_putchar(' ');
		arg = arg->next;
	}
	if (has_flag)
		ft_putstr("\n");
}
