/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:30:10 by otodd             #+#    #+#             */
/*   Updated: 2024/08/06 13:31:49 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(void)
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

static void	ft_parser_reorder_tokens(
	t_root *rt, t_token *i_tkn, t_token **tkn, t_token *if_tkn)
{
	ft_token_move_before(i_tkn, *tkn);
	ft_token_move_before(if_tkn, i_tkn);
	*tkn = if_tkn;
	if (!(*tkn)->prev)
		rt->ctx_tokens = *tkn;
}

static void	ft_parser_do_checks(
	t_root *rt, t_token *i_tkn, t_token **tkn)
{
	t_token	*if_tkn;

	if (i_tkn->type == INPUT && i_tkn->next->type == INPUT_FILE)
	{
		if_tkn = i_tkn->next;
		ft_parser_reorder_tokens(rt, i_tkn, tkn, if_tkn);
	}
	else if (i_tkn->type == HEREDOC && i_tkn->next->type == INPUT_FILE)
	{
		if_tkn = i_tkn->next;
		if_tkn->str = ft_handle_heredoc(if_tkn->str);
		ft_parser_reorder_tokens(rt, i_tkn, tkn, if_tkn);
	}
}

void	ft_parser_check_for_input_or_heredoc(t_root *root, t_token **token)
{
	t_token	*input_token;

	if ((*token)->type != CMD)
		return ;
	if (!(*token)->next)
		return ;
	input_token = (*token)->next;
	while (input_token)
	{
		if (input_token->type == ARG)
		{
			input_token = input_token->next;
			continue ;
		}
		ft_parser_do_checks(root, input_token, token);
		break ;
	}
}

bool	ft_parser_adjust_tokens(t_root *root)
{
	t_token	*token;

	token = root->ctx_tokens;
	if (!token)
		return (false);
	while (token)
	{
		ft_parser_check_for_input_or_heredoc(root, &token);
		token = token->next;
	}
	ft_token_reindex(root->ctx_tokens);
	return (true);
}
