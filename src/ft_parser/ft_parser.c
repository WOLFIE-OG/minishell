/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:01:05 by otodd             #+#    #+#             */
/*   Updated: 2024/08/07 18:20:51 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_parser_handle_tokens(t_root *root, t_token *token, t_cmd *cmd)
{
	if (!cmd->cmd_tokens)
	{
		cmd->cmd_tokens = ft_token_dup(token);
		cmd->is_builtin = ft_is_builtin(root, cmd->cmd_tokens->str);
	}
	else
		ft_token_add(&cmd->cmd_tokens, ft_token_dup(token));
	if (cmd->cmd_tokens->type == INPUT_FILE)
		cmd->execute = false;
}

static void	ft_parser_handle_cmds(t_token *token, t_cmd **cmd)
{
	(*cmd)->post_action = token->type;
	if (token->next)
	{
		(*cmd)->next = ft_new_cmd();
		*cmd = (*cmd)->next;
	}
}

t_cmd	*ft_parser(t_root *root)
{
	t_token	*token;
	t_cmd	*cmd;
	t_cmd	*head;

	if (!ft_parser_adjust_tokens(root))
		return (NULL);
	token = root->preped_tokens;
	cmd = ft_new_cmd();
	head = cmd;
	while (token)
	{
		token->str = ft_expand_str(root, token->str);
		if (token->type == CMD || token->type == ARG || token->type == EMPTY
			|| token->type == INPUT_FILE)
			ft_parser_handle_tokens(root, token, cmd);
		else
			ft_parser_handle_cmds(token, &cmd);
		token = token->next;
	}
	if (!head)
		return (NULL);
	ft_gc_tokens(root->preped_tokens);
	return (head);
}
