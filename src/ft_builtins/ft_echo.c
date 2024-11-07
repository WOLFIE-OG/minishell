/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/11/07 17:37:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo_flag_check(t_root *root, int *arg_n, bool *apply_nl)
{
	t_token	*args;

	args = root->current_cmd->cmd_tokens->next;
	while (args)
	{
		if (args->str[0] == '-' && ft_strrep(&args->str[0], '-') <= 1
			&& args->state == NORMAL)
		{
			if (ft_strrep(&args->str[1], 'n'))
			{
				*arg_n += 1;
				*apply_nl = false;
			}
		}
		else
			break ;
		args = args->next;
	}
}

static int	ft_echo_output_ex(char *str, t_cmd *cmd)
{
	char	*tmp;

	if (ft_strlen(str) > 4096 && cmd->next)
	{
		tmp = ft_write_to_tmp("minishell_tmp_echo", str, true, cmd->pipe[0]);
		free(str);
		if (!tmp)
			return (EXIT_FAILURE);
		free(tmp);
	}
	else
		ft_putstr_fd(str, STDOUT_FILENO);
	free(str);
	return (EXIT_SUCCESS);
}

static int	ft_echo_output(t_cmd *cmd, int arg_n, bool apply_nl)
{
	t_token	*arg;
	char	**str_arr;
	char	*str;

	str_arr = NULL;
	str = NULL;
	arg = ft_find_token_by_index(cmd->cmd_tokens, arg_n);
	if (!arg && !apply_nl)
		return (EXIT_SUCCESS);
	while (arg)
	{
		str_arr = ft_strarrayappend2(str_arr, ft_strdup(arg->str));
		if (arg->next)
			str_arr = ft_strarrayappend2(str_arr, ft_strdup(" "));
		arg = arg->next;
	}
	if (apply_nl)
		str_arr = ft_strarrayappend2(str_arr, ft_strdup("\n"));
	str = ft_strarraytostr(str_arr);
	ft_gc_str_array(str_arr);
	return (ft_echo_output_ex(str, cmd));
}

int	ft_echo(t_cmd *cmd)
{
	int		arg_n;
	bool	apply_nl;

	arg_n = 1;
	apply_nl = true;
	ft_echo_flag_check(cmd->root, &arg_n, &apply_nl);
	return (ft_echo_output(cmd, arg_n, apply_nl));
}
