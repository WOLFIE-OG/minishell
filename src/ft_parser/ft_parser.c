/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:01:05 by otodd             #+#    #+#             */
/*   Updated: 2024/08/30 17:11:18 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_parser_is_builtin(char *cmd)
{
	const char	*builtin_array[8] = {"cd", "export", "env", "unset", "exit",
		"echo", "pwd", NULL};

	if (ft_is_in_strarray((char **)builtin_array, cmd))
		return (true);
	else
		return (false);
}

static void	ft_parser_handle_tokens(t_root *root, t_token *token, t_cmd *cmd)
{
	if (token->type == CMD && !cmd->execute)
	{
		cmd->execute = true;
		root->prev_cmd = cmd;
	}
	if (!cmd->cmd_tokens)
	{
		cmd->cmd_tokens = ft_token_dup(token);
		cmd->is_builtin = ft_parser_is_builtin(cmd->cmd_tokens->str);
	}
}

static void	ft_parser_handle_arg_tokens(t_token *token, t_cmd *cmd)
{
	if (!cmd->cmd_tokens)
		cmd->cmd_tokens = ft_token_dup(token);
	else
		ft_token_add(&cmd->cmd_tokens, ft_token_dup(token));
}

static void	ft_parser_handle_cmds(t_token *token, t_cmd **cmd)
{
	(*cmd)->post_action = token->type;
	if (token->next)
	{
		(*cmd)->next = ft_new_cmd();
		(*cmd)->next->prev = *cmd;
		*cmd = (*cmd)->next;
	}
}

void	ft_parser(t_root *root)
{
	t_token	*token;
	t_cmd	*cmd;
	t_cmd	*head;

	if (!ft_parser_adjust_tokens(root))
		return ;
	token = root->preped_tokens;
	cmd = ft_new_cmd();
	head = cmd;
	while (token)
	{
		if (token->type == CMD || token->type == EMPTY
			|| token->type == INPUT_FILE || token->type == OUTPUT_FILE)
			ft_parser_handle_tokens(root, token, cmd);
		else if (token->type == ARG)
			ft_parser_handle_arg_tokens(token, root->prev_cmd);
		else
			ft_parser_handle_cmds(token, &cmd);
		token = token->next;
	}
	if (!head)
		return ;
	ft_gc_tokens(root->preped_tokens);
	root->preped_cmds = head;
	root->prev_cmd = NULL;
	return ;
}
