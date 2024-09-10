/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:38 by otodd             #+#    #+#             */
/*   Updated: 2024/09/10 21:56:07 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_expansion(t_root *root, t_str_expansion *vars)
{
	vars->before_var = ft_substr(*vars->split_str, 0,
			(vars->tkn_str - *vars->split_str));
	vars->after_var = vars->tkn_str + 1;
	while ((*vars->after_var && ft_isalnum(*vars->after_var))
		|| *vars->after_var == '?' || *vars->after_var == '_')
		vars->after_var++;
	vars->tmp_str = ft_strdup(vars->after_var);
	vars->tkn_str = ft_substr((vars->tkn_str + 1), 0,
			((vars->after_var - vars->tkn_str) - 1));
	vars->var = ft_get_var(root, vars->tkn_str);
	ft_expansion_helper(root, vars);
	free(vars->tkn_str);
	free(vars->before_var);
	if (vars->tmp_str)
	{
		vars->tkn_str = *vars->split_str;
		*vars->split_str = ft_strjoin(vars->tkn_str, vars->tmp_str);
		free(vars->tmp_str);
		free(vars->tkn_str);
	}
}

static void	ft_expansion_home(t_root *root, t_str_expansion *vars)
{
	vars->after_var = vars->tkn_str + 1;
	vars->tmp_str = ft_strdup(vars->after_var);
	vars->var = ft_get_var(root, "HOME");
	free(*vars->split_str);
	*vars->split_str = ft_strjoin(vars->var->value, vars->tmp_str);
	free(vars->tmp_str);
}

static void	ft_expansion_loop(t_root *root, t_str_expansion *vars, bool tilde)
{
	while (*vars->split_str)
	{
		vars->tkn_str = ft_strchr(*vars->split_str, '$');
		if (vars->tkn_str)
		{
			if (!*(vars->tkn_str + 1))
			{
				vars->split_str++;
				continue ;
			}
			ft_expansion(root, vars);
		}
		else if (tilde)
		{
			vars->tkn_str = *vars->split_str;
			if (vars->tkn_str)
				ft_expansion_home(root, vars);
		}
		vars->result_array = ft_strarrayappend2(vars->result_array,
				ft_strdup(*vars->split_str));
		if (*(vars->split_str + 1))
			vars->result_array = ft_strarrayappend2(vars->result_array,
					ft_strdup(" "));
		vars->split_str++;
	}
}

char	*ft_expand_str(t_root *root, char *str, bool tilde)
{
	t_str_expansion	vars;
	char			*expanded_str;

	if (!str)
		return (NULL);
	vars.split_str = ft_split(str, ' ');
	vars.tkn_head = vars.split_str;
	vars.result_array = NULL;
	ft_expansion_loop(root, &vars, tilde);
	if (vars.result_array)
		expanded_str = ft_strarraytostr(vars.result_array);
	else
		expanded_str = ft_strdup(str);
	ft_gc_str_array(vars.result_array);
	ft_gc_str_array(vars.tkn_head);
	free(str);
	return (expanded_str);
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
