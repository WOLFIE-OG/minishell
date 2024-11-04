/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:57:17 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 14:30:34 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_cmd *cmd, bool declare)
{
	char	*tmp;
	char	*env;
	char	**env_arr;

	if (declare)
		env_arr = ft_env_to_declare_array(cmd->root);
	else
		env_arr = ft_env_to_array(cmd->root, true);
	env = ft_strarraytostr(env_arr);
	if (ft_strlen(env) > 4096 && cmd->next)
	{
		tmp = ft_write_to_tmp("minishell_tmp_env_cmd", env, true, cmd->pipe[0]);
		if (!tmp)
		{
			free(env);
			ft_gc_str_array(env_arr);
			return (EXIT_FAILURE);
		}
		free(tmp);
	}
	else
		ft_putstr(env);
	free(env);
	ft_gc_str_array(env_arr);
	return (EXIT_SUCCESS);
}
