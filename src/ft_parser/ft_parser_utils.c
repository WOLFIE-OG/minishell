/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:30:10 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 16:22:24 by otodd            ###   ########.fr       */
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

void	ft_parser_check_for_input(t_root *root, t_token **token)
{
	t_token	*input_token;
	t_token	*input_file_token;

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
		if (input_token->type == INPUT && input_token->next->type == INPUT_FILE)
		{
			input_file_token = input_token->next;
			ft_token_move_before(input_token, *token);
			ft_token_move_before(input_file_token, input_token);
			*token = input_file_token;
			if (!(*token)->prev)
				root->ctx_tokens = *token;
		}
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
		ft_parser_check_for_input(root, &token);
		token = token->next;
	}
	ft_token_reindex(root->ctx_tokens);
	return (true);
}
