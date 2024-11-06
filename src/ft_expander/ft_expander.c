/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:38 by otodd             #+#    #+#             */
/*   Updated: 2024/11/05 23:48:16 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_expansion(t_root *root, t_str_expansion *vars, char *str)
{
	vars->tkn_str = str;
	vars->after_var = vars->tkn_str;
	while (*vars->after_var && (ft_isalnum(*vars->after_var)
			|| *vars->after_var == '_'))
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
		if (*str == '$' && (*(str + 1) && (ft_isalnum(*(str + 1))
					|| *(str + 1) == '?')))
		{
			str++;
			var = str;
			while (*var && (ft_isalnum(*var) || *var == '?' || *var == '_'))
				var++;
			vars->tmp_str2 = ft_substr(str, 0, (var - str));
			vars->tmp_str = ft_expansion(root, vars, vars->tmp_str2);
			free(vars->tmp_str2);
			vars->tmp_str2 = ft_strjoin(vars->new_str, vars->tmp_str);
			free(vars->new_str);
			free(vars->tmp_str);
			vars->new_str = vars->tmp_str2;
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
	free(vars.new_str);
	if (tilde)
	{
		vars.var = ft_get_var(root, "HOME");
		if (!vars.var)
			vars.tmp_str = "(null)";
		else
			vars.tmp_str = vars.var->value;
		vars.tmp_str = ft_strjoin(vars.tmp_str, (vars.expanded_str + 1));
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
		vars->expanded_tokens = ft_expander_tokenizer(vars->tkn_head);
		if (vars->expanded_tokens)
			ft_expander_expand_tokens(vars);
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
