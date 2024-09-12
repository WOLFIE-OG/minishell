/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/09/12 18:26:10 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_root *root)
{
	char	**temp;
	t_token	*args;

	args = root->current_cmd->cmd_tokens;
	if (!args)
		ft_env(root);
	args = args->next;
	while (args)
	{
		temp = ft_key_value(args->str, '=');
		if (temp[1] && ft_strlen(temp[0]))
		{
			if (!ft_ischeck_str(temp[0], ft_isalnum)
				|| ft_isvalid_numstr(temp[0]))
			{
				ft_fprintf(STDERR_FILENO, "minishell: export: `%s': %s\n",
					temp[0], "not a valid identifier");
				ft_gc_str_array(temp);
				return (EXIT_FAILURE);
			}
			ft_set_var(root, temp[0], ft_strdup(temp[1]));
		}
		ft_gc_str_array(temp);
		args = args->next;
	}
	return (EXIT_SUCCESS);
}
