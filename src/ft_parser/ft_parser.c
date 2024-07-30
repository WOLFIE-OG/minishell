/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:01:05 by otodd             #+#    #+#             */
/*   Updated: 2024/07/30 18:05:22 by otodd            ###   ########.fr       */
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
	cmd->is_builtin = false;
	cmd->execute = true;
	
	return (cmd);
}

t_cmd	*ft_parser(t_root *root)
{
	t_token	*token;
	t_cmd	*cmd;
	t_cmd	*head;

	token = root->ctx_tokens;
	if (!token)
		return (NULL);
	cmd = ft_new_cmd();
	head = cmd;
	while (token)
	{
		if (token->type == CMD)
		{
			if (token->next && token->next->next)
			{
				if (token->next->type == INPUT && token->next->next->type == INPUT_FILE)
				{
					ft_token_swap(token, token->next->next);
					token = token->prev->prev;
				}
			}
		}
		if (token->type == CMD
			|| token->type == ARG
			|| token->type == EMPTY
			|| token->type == INPUT_FILE)
		{
			if (!cmd->cmd_tokens)
			{
				cmd->cmd_tokens = ft_token_dup(token);
				cmd->is_builtin = ft_is_builtin(root, cmd->cmd_tokens->str);
			}
			else
				ft_token_add(&cmd->cmd_tokens, ft_token_dup(token));
		}
		else
		{
			cmd->post_action = token->type;
			if (cmd->cmd_tokens->type == INPUT_FILE)
				cmd->execute = false;
			if (token->next)
			{
				cmd->next = ft_new_cmd();
				cmd = cmd->next;
			}
		}
		token = token->next;
	}
	if (!head)
		return (NULL);
	return (head);
}
