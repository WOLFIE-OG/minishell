/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:01:05 by otodd             #+#    #+#             */
/*   Updated: 2024/07/30 00:41:59 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	pipe(cmd->pipe);
	cmd->post_action = EMPTY;
	cmd->next = NULL;
	cmd->cmd_tokens = NULL;
	return (cmd);
}

t_cmd	*ft_parser(t_root *root)
{
	t_token	*token;
	t_cmd	*cmd;
	t_cmd	*head;
	t_cmd	*prev_cmd;

	token = root->tokens;
	if (!token)
		return (NULL);
	cmd = ft_new_cmd();
	head = cmd;
	prev_cmd = NULL;
	while (token)
	{
		if (token->type == CMD
			|| token->type == ARG
			|| token->type == EMPTY
			|| token->type == INPUT_FILE)
		{
			if (!cmd->cmd_tokens)
				cmd->cmd_tokens = ft_token_dup(token);
			else
				ft_token_add(&cmd->cmd_tokens, ft_token_dup(token));
		}
		else
		{
			if (prev_cmd)
				prev_cmd->next = cmd;
			cmd->post_action = token->type;
			prev_cmd = cmd;
			cmd = ft_new_cmd();
		}
		token = token->next;
	}
	if (prev_cmd)
		prev_cmd->next = cmd;
	if (!head)
		return (NULL);
	return (head);
}
