/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:13:11 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 16:18:39 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_expander_expand_tokens(t_expander_vars *vars)
{
	free(vars->tkn_head->str);
	vars->tkn_head->str = ft_strdup(vars->expanded_tokens->str);
	vars->next_token = vars->tkn_head->next;
	vars->remaining_arg_tokens = vars->expanded_tokens->next;
	while (vars->remaining_arg_tokens)
	{
		vars->duped_token = ft_token_dup(vars->remaining_arg_tokens);
		ft_token_insert(vars->tkn_head, vars->duped_token);
		vars->tkn_head = vars->duped_token;
		vars->remaining_arg_tokens = vars->remaining_arg_tokens->next;
	}
	if (vars->next_token)
	{
		vars->tkn_head->next = vars->next_token;
		vars->next_token->prev = vars->tkn_head;
	}
	ft_gc_tokens(vars->expanded_tokens);
	ft_token_reindex(vars->cmd_head->cmd_tokens);
}
