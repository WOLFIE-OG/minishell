/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:38 by otodd             #+#    #+#             */
/*   Updated: 2024/08/12 17:26:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_expansion_helper(t_root *root, t_str_expansion *vars)
{
	free(*vars->split);
	if (ft_strcmp(vars->pre, "\\") == 0)
		*vars->split = ft_strjoin("$", vars->str);
	else if (vars->var)
		*vars->split = ft_strjoin(vars->pre, vars->var->value);
	else
	{
		if (ft_strcmp(vars->str, "?") == 0)
			*vars->split = ft_itoa(root->prev_cmd_status);
		else
			*vars->split = ft_strdup("");
	}
}

static void	ft_expansion(t_root *root, t_str_expansion *vars)
{
	vars->pre = ft_substr(*vars->split, 0, (vars->str - *vars->split));
	vars->post = vars->str + 1;
	while ((*vars->post && ft_isalnum(*vars->post))
		|| *vars->post == '?')
		vars->post++;
	vars->tmp = ft_strdup(vars->post);
	vars->str = ft_substr((vars->str + 1), 0, ((vars->post - vars->str) - 1));
	vars->var = ft_get_var(root, vars->str);
	ft_expansion_helper(root, vars);
	free(vars->str);
	free(vars->pre);
	if (vars->tmp)
	{
		vars->str = *vars->split;
		*vars->split = ft_strjoin(vars->str, vars->tmp);
		free(vars->tmp);
		free(vars->str);
	}
}

static void	ft_expansion_loop(t_root *root, t_str_expansion *vars)
{
	while (*vars->split)
	{
		vars->str = ft_strchr(*vars->split, '$');
		if (vars->str)
		{
			if (!*(vars->str + 1))
			{
				vars->split++;
				continue ;
			}
			ft_expansion(root, vars);
		}
		vars->arr = ft_strarrayappend2(vars->arr, ft_strdup(*vars->split));
		if (*(vars->split + 1))
			vars->arr = ft_strarrayappend2(vars->arr, ft_strdup(" "));
		vars->split++;
	}
}

char	*ft_expand_str(t_root *root, char *str)
{
	t_str_expansion	vars;
	char			*expanded_str;

	if (!str)
		return (NULL);
	vars.split = ft_split(str, ' ');
	vars.head = vars.split;
	vars.arr = NULL;
	ft_expansion_loop(root, &vars);
	if (vars.arr)
		expanded_str = ft_strarraytostr(vars.arr);
	else
		expanded_str = ft_strdup(str);
	ft_gc_str_array(vars.arr);
	ft_gc_str_array(vars.head);
	free(str);
	return (expanded_str);
}
