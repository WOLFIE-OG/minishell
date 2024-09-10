/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:01:05 by otodd             #+#    #+#             */
/*   Updated: 2024/09/10 13:04:50 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_parser_handle_tokens(t_root *root, t_parser_vars *vars)
{
	if (vars->tkn->type == OUTPUT_FILE
		|| vars->tkn->type == INPUT_FILE
		|| vars->tkn->type == HEREDOC_DELIM)
		vars->cmd->is_file = true;
	if (vars->tkn->type == CMD && !vars->cmd->execute)
	{
		vars->cmd->execute = true;
		root->prev_cmd = vars->cmd;
	}
	if (!vars->cmd->cmd_tokens)
	{
		vars->cmd->cmd_tokens = ft_token_dup(vars->tkn);
		vars->cmd->is_builtin = ft_parser_is_builtin(
				vars->cmd->cmd_tokens->str);
	}
}

static void	ft_parser_handle_arg_tokens(t_parser_vars *vars, t_cmd *cmd)
{
	if (!cmd->cmd_tokens)
		cmd->cmd_tokens = ft_token_dup(vars->tkn);
	else
		ft_token_add(&cmd->cmd_tokens, ft_token_dup(vars->tkn));
}

static void	ft_parser_handle_cmds(t_parser_vars *vars)
{
	vars->cmd->post_action = vars->tkn->type;
	if (vars->tkn->next)
	{
		vars->cmd->next = ft_new_cmd();
		vars->cmd->next->prev = vars->cmd;
		vars->cmd = vars->cmd->next;
	}
}

static void	ft_parser_loop(t_root *root, t_parser_vars *vars)
{
	if (vars->tkn->type == CMD
		|| vars->tkn->type == EMPTY
		|| vars->tkn->type == INPUT_FILE
		|| vars->tkn->type == OUTPUT_FILE
		|| vars->tkn->type == HEREDOC_DELIM)
		ft_parser_handle_tokens(root, vars);
	else if (vars->tkn->type == ARG)
		ft_parser_handle_arg_tokens(vars, root->prev_cmd);
	else
		ft_parser_handle_cmds(vars);
	vars->tkn = vars->tkn->next;
}

void	ft_parser(t_root *root)
{
	t_parser_vars	vars;

	if (!ft_parser_adjust_tokens(root))
		return ;
	vars.tkn = root->preped_tokens;
	vars.cmd = ft_new_cmd();
	vars.head = vars.cmd;
	while (vars.tkn)
		ft_parser_loop(root, &vars);
	if (!vars.head)
		return ;
	ft_gc_tokens(root->preped_tokens);
	root->preped_cmds = vars.head;
	root->prev_cmd = NULL;
	return ;
}
