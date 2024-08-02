/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_gc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:58:28 by otodd             #+#    #+#             */
/*   Updated: 2024/08/01 16:04:39 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_gc_preped_cmds(t_root *root)
{
	t_cmd	*head;
	t_cmd	*next;

	head = root->preped_cmds;
	while (head)
	{
		next = head->next;
		ft_gc_tokens(head->cmd_tokens);
		close(head->pipe[0]);
		close(head->pipe[1]);
		free(head);
		head = next;
	}
}
