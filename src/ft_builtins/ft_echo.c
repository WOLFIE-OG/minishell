/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/07/31 18:35:09 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo_flag_check(t_token *flag, int *arg_n, bool *has_flag)
{
	if (flag->str[0] == '-')
	{
		if (ft_strrep(&flag->str[1], 'n'))
		{
			*arg_n = 2;
			*has_flag = true;
		}
	}
}

static void	ft_echo_output(t_root *root, int arg_n, bool has_flag)
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
	if (has_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	ft_echo(t_root *root)
{
	int		arg_n;
	bool	has_flag;
	t_token	*flag;

	arg_n = 1;
	has_flag = false;
	flag = ft_find_token_by_index(root->current_cmd->cmd_tokens, 1);
	if (!flag)
		return (EXIT_FAILURE);
	ft_echo_flag_check(flag, &arg_n, &has_flag);
	ft_echo_output(root, arg_n, has_flag);
	return (EXIT_SUCCESS);
}
