/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 15:29:24 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo_flag_check(t_token *flag, int *arg_n, bool *apply_nl)
{
	if (flag->str[0] == '-')
	{
		if (ft_strrep(&flag->str[1], 'n'))
		{
			*arg_n = 2;
			*apply_nl = false;
		}
	}
}

static void	ft_echo_output(t_root *root, int arg_n, bool apply_nl)
{
	t_token	*arg;

	arg = ft_find_token_by_index(root->current_cmd->cmd_tokens, arg_n);
	while (arg)
	{
		ft_putstr_fd(arg->str, STDOUT_FILENO);
		if (arg->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		arg = arg->next;
	}
	if (apply_nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	ft_echo(t_root *root)
{
	int		arg_n;
	bool	apply_nl;
	t_token	*flag;

	arg_n = 1;
	apply_nl = true;
	flag = ft_find_token_by_index(root->current_cmd->cmd_tokens, 1);
	if (!flag)
		return (EXIT_FAILURE);
	ft_echo_flag_check(flag, &arg_n, &apply_nl);
	ft_echo_output(root, arg_n, apply_nl);
	return (EXIT_SUCCESS);
}
