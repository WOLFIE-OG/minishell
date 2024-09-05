/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:30:10 by otodd             #+#    #+#             */
/*   Updated: 2024/09/05 17:45:18 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->post_action = EMPTY;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->cmd_tokens = NULL;
	cmd->is_builtin = false;
	cmd->execute = false;
	cmd->pid = 0;
	return (cmd);
}

static void	ft_parser_do_checks(
	t_root *rt, t_token *i_tkn, t_token **tkn)
{
	if (i_tkn->type == INPUT && i_tkn->next->type == INPUT_FILE)
		ft_parser_arrange_input(rt, i_tkn, tkn);
	else if (i_tkn->type == HEREDOC && i_tkn->next->type == HEREDOC_DELIM)
		ft_parser_arrange_heredoc(rt, i_tkn, tkn);
	else if (i_tkn->type == INPUT_FILE
		&& (i_tkn->prev && i_tkn->prev->type == INPUT) && !i_tkn->prev->prev)
		ft_parser_arrange_input_alt(rt, i_tkn, tkn);
	else if (i_tkn->type == HEREDOC_DELIM
		&& (i_tkn->prev && i_tkn->prev->type == HEREDOC) && !i_tkn->prev->prev)
		ft_parser_arrange_heredoc_alt(rt, i_tkn, tkn);
	else if (i_tkn->type == OUTPUT_FILE
		&& (i_tkn->prev && (i_tkn->prev->type == TRUNC
				|| i_tkn->prev->type == APPEND)) && !i_tkn->prev->prev)
		ft_parser_arrange_trunc_append(rt, i_tkn, tkn);
}

void	ft_parser_check_for_input_or_heredoc(t_root *root, t_token **token)
{
	t_token	*input_token;

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

	token = root->preped_tokens;
	if (!token)
		return (false);
	while (token)
	{
		ft_parser_check_for_input_or_heredoc(root, &token);
		token = token->next;
	}
	ft_token_reindex(root->preped_tokens);
	return (true);
}

bool	ft_parser_is_builtin(char *cmd)
{
	const char	*builtin_array[8] = {"cd", "export", "env", "unset", "exit",
		"echo", "pwd", NULL};

	if (ft_is_in_strarray((char **)builtin_array, cmd))
		return (true);
	else
		return (false);
}
