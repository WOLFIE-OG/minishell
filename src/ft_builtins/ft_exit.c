/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:33 by otodd             #+#    #+#             */
/*   Updated: 2024/11/06 16:04:48 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isvalid_numstr_alt(char *s)
{
	int	num;
	int	non_num;

	num = 0;
	non_num = 0;
	if ((*s == '-' || *s == '+') && *(s + 1))
		s++;
	while (*s)
	{
		if (ft_isdigit(*s))
			num++;
		else if (!ft_isdigit(*s) && !ft_iswhitespace(*s))
			non_num++;
		s++;
	}
	if (!num || non_num > 0)
		return (0);
	return (1);
}

void	ft_exit(t_root *root)
{
	t_token		*args;
	long long	code;

	if (root->current_cmd->next)
		return ;
	args = root->current_cmd->cmd_tokens;
	if (args && !args->next)
	{
		root->exit = true;
		root->current_cmd->exit_code = root->prev_cmd_status;
		return ;
	}
	args = args->next;
	if (!ft_isvalid_numstr_alt(args->str))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args->str);
		root->exit = true;
		root->current_cmd->exit_code = 2;
		return ;
	}
	if (args->next)
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		root->current_cmd->exit_code = EXIT_FAILURE;
		return ;
	}
	root->exit = true;
	code = (long long)ft_atol(args->str);
	if (code <= LONG_MIN + 1 || code >= LONG_MAX - 1)
	{
		ft_fprintf(STDERR_FILENO, "exit: %q: numeric argument required\n",
			code);
		root->exit = true;
		root->current_cmd->exit_code = 2;
		return ;
	}
	root->current_cmd->exit_code = code;
	return ;
}
