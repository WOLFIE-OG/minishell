/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:33 by otodd             #+#    #+#             */
/*   Updated: 2024/11/11 17:19:34 by otodd            ###   ########.fr       */
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

static bool	ft_exit_helper(t_root *root, t_token **args)
{
	*args = root->current_cmd->cmd_tokens;
	if (args && !(*args)->next)
	{
		root->exit = true;
		root->current_cmd->exit_code = root->prev_cmd_status;
		return (false);
	}
	*args = (*args)->next;
	if (!ft_isvalid_numstr_alt((*args)->str))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			(*args)->str);
		root->exit = true;
		root->current_cmd->exit_code = 2;
		return (false);
	}
	if ((*args)->next)
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		root->current_cmd->exit_code = EXIT_FAILURE;
		return (false);
	}
	return (true);
}

void	ft_exit(t_root *root)
{
	t_token		*args;
	long long	code;

	if (root->current_cmd->next)
		return ;
	if (!ft_exit_helper(root, &args))
		return ;
	root->exit = true;
	code = (long long)ft_atol(args->str);
	if (code < LONG_MIN && code > LONG_MAX)
	{
		printf("exit: %lld: numeric argument required\n",
			code);
		root->current_cmd->exit_code = 2;
		return ;
	}
	root->current_cmd->exit_code = code;
	return ;
}
