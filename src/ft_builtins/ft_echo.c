/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/09/18 03:25:32 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo_flag_check(t_root *root, int *arg_n, bool *apply_nl)
{
	t_token	*args;

	args = root->current_cmd->cmd_tokens;
	while (args)
	{
		if (args->str[0] == '-' && ft_strrep(&args->str[0], '-'))
		{
			if (ft_strrep(&args->str[1], 'n'))
			{
				*arg_n += 1;
				*apply_nl = false;
			}
		}
		args = args->next;
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

	arg_n = 1;
	apply_nl = true;
	ft_echo_flag_check(root, &arg_n, &apply_nl);
	ft_echo_output(root, arg_n, apply_nl);
	return (EXIT_SUCCESS);
}
