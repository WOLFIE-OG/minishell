/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:40:23 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 17:40:06 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_isalnum_alt(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (8);
	return (0);
}

static void	ft_export_helper(t_root *root, t_token *args, int *return_c)
{
	char	**temp;

	temp = ft_key_value(args->str, '=');
	if (temp[1] && ft_strlen(temp[0]))
	{
		if (!ft_ischeck_str(temp[0], ft_isalnum_alt))
		{
			ft_fprintf(STDERR_FILENO, "export: `%s=%s': %s\n",
				temp[0], temp[1], "not a valid identifier");
			*return_c = EXIT_FAILURE;
		}
		else
			ft_set_var(root, temp[0], ft_strdup(temp[1]));
	}
	ft_gc_str_array(temp);
}

int	ft_export(t_root *root)
{
	t_token	*args;
	int		return_c;

	return_c = EXIT_SUCCESS;
	args = root->current_cmd->cmd_tokens;
	if (args && !args->next)
		return (ft_env(root->current_cmd, true));
	args = args->next;
	while (args)
	{
		ft_export_helper(root, args, &return_c);
		args = args->next;
	}
	return (return_c);
}
