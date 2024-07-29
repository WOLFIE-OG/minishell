/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:48:10 by otodd             #+#    #+#             */
/*   Updated: 2024/07/29 17:24:19 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_is_builtin(t_root *root, char *cmd)
{
	if (ft_is_in_strarray(root->builtin_array, cmd))
		return (true);
	else
		return (false);
}

char	**ft_exec_arg_str(t_root *root)
{
	char	**arg;
	t_token	*head;

	arg = NULL;
	head = root->current_cmd->cmd_tokens;
	while (head)
	{
		arg = ft_strarrayappend2(arg, ft_strdup(head->str));
		head = head->next;
	}
	return (arg);
}
