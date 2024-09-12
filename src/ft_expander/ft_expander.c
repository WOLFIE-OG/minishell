/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:38 by otodd             #+#    #+#             */
/*   Updated: 2024/09/12 17:10:38 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_expansion(t_root *root, t_str_expansion *vars, char *str)
{
	vars->tkn_str = str;
	vars->after_var = vars->tkn_str;
	while (*vars->after_var && ft_isalnum(*vars->after_var))
		vars->after_var++;
	if (vars->after_var)
	{
		vars->tmp_str = ft_substr(vars->tkn_str, 0,
				(vars->after_var - vars->tkn_str));
		vars->var = ft_get_var(root, vars->tmp_str);
		free(vars->tmp_str);
	}
	else
		vars->var = ft_get_var(root, vars->tkn_str);
	if (vars->var)
		return (ft_strjoin(vars->var->value, vars->after_var));
	else
	{
		if (ft_strcmp(vars->tkn_str, "?") == 0)
			return (ft_itoa(root->prev_cmd_status));
		return (ft_strdup(""));
	}
}

static void	ft_expansion_loop(t_root *root, t_str_expansion *vars, char *str)
{
	char	*var;

	vars->new_str = ft_strdup("");
	while (*str)
	{
		if (*str == '$' && (*(str + 1) && ft_isalnum(*(str + 1))))
		{
			str++;
			var = str;
			while (*var && ft_isalnum(*var))
				var++;
			vars->new_str = ft_strjoin(
					vars->new_str,
					ft_expansion(root, vars, ft_substr(str, 0, (var - str))));
			str = var;
		}
		else
			vars->new_str = ft_strappend(vars->new_str, *str++);
	}
}

char	*ft_expand_str(t_root *root, char *str, bool tilde)
{
	t_str_expansion	vars;

	if (!str)
		return (NULL);
	ft_expansion_loop(root, &vars, str);
	vars.expanded_str = ft_strdup(vars.new_str);
	free(str);
	if (tilde)
	{
		vars.var = ft_get_var(root, "HOME");
		vars.tmp_str = ft_strjoin(vars.var->value, (vars.expanded_str + 1));
		free(vars.expanded_str);
		vars.expanded_str = vars.tmp_str;
	}
	return (vars.expanded_str);
}

void	ft_expander_helper(t_root *root, t_expander_vars *vars)
{
	bool	tilde;

	tilde = (*vars->tkn_head->str == '~' && (!*(vars->tkn_head->str + 1)
				|| *(vars->tkn_head->str + 1) != '$')
			&& vars->tkn_head->state == NORMAL);
	if (ft_strchr(vars->tkn_head->str, '$') || tilde)
	{
		vars->tkn_head->str = ft_expand_str(root, vars->tkn_head->str, tilde);
		vars->expanded_tokens = ft_expander_tokenizer(vars->tkn_head->str);
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

void	ft_expander(t_root *root)
{
	t_expander_vars	vars;

	vars.cmd_head = root->preped_cmds;
	while (vars.cmd_head)
	{
		vars.tkn_head = vars.cmd_head->cmd_tokens;
		while (vars.tkn_head)
		{
			if (vars.tkn_head->type != HEREDOC_DELIM
				&& vars.tkn_head->state != SINGLE_Q)
				ft_expander_helper(root, &vars);
			vars.tkn_head = vars.tkn_head->next;
		}
		vars.cmd_head = vars.cmd_head->next;
	}
}
