/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:16:26 by otodd             #+#    #+#             */
/*   Updated: 2024/09/10 18:21:12 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_expansion_helper(t_root *root, t_str_expansion *vars)
{
	free(*vars->split_str);
	if (vars->var)
		*vars->split_str = ft_strjoin(vars->before_var, vars->var->value);
	else
	{
		if (ft_strcmp(vars->tkn_str, "?") == 0)
			*vars->split_str = ft_itoa(root->prev_cmd_status);
		else
			*vars->split_str = ft_strdup("");
	}
}

void	ft_expansion_helper_tilde(t_str_expansion *vars)
{
	char	*trimmed_var;

	if (vars->var)
	{
		trimmed_var = ft_trim_start_end(vars->var->value, "\"'");
		*vars->split_str = trimmed_var;
	}
}

void	ft_expander_helper(t_root *root, t_expander_vars *vars)
{
	bool	tilde;

	tilde = (vars->tkn_head->str[0] == '~');
	if (ft_strchr(vars->tkn_head->str, '$') || tilde)
	{
		vars->tkn_head->str = ft_expand_str(root, vars->tkn_head->str, tilde);
		vars->expanded_tokens = ft_tokenizer(vars->tkn_head->str);
		if (vars->expanded_tokens)
		{
			free(vars->tkn_head->str);
			vars->tkn_head->str = ft_strdup(vars->expanded_tokens->str);
			vars->remaining_arg_tokens = vars->expanded_tokens->next;
			while (vars->remaining_arg_tokens)
			{
				vars->duped_token = ft_token_dup(vars->remaining_arg_tokens);
				ft_token_insert(vars->tkn_head, vars->duped_token);
				vars->tkn_head = vars->duped_token;
				vars->remaining_arg_tokens = vars->remaining_arg_tokens->next;
			}
			ft_gc_tokens(vars->expanded_tokens);
			ft_token_reindex(vars->cmd_head->cmd_tokens);
		}
	}
}
