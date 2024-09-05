/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:12 by otodd             #+#    #+#             */
/*   Updated: 2024/09/03 18:19:55 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_heredoc_do_checks(t_root *root, t_heredoc_data *vars)
{
	char	*str;

	if (ft_strcmp(vars->input, vars->delim) == 0)
	{
		vars->end = true;
		free(vars->input);
	}
	else
	{
		if (vars->expand)
			str = ft_expand_str(root, vars->input);
		else
		{
			str = ft_strdup(vars->input);
			free(vars->input);
		}
		vars->data = ft_strarrayappend2(vars->data, str);
		vars->data = ft_strarrayappend2(vars->data, ft_strdup("\n"));
	}
}

static char	*ft_heredoc_result_clean_up(char **data)
{
	char	*result;

	result = ft_strarraytostr(data);
	if (!result)
		result = ft_strdup("\0");
	ft_gc_str_array(data);
	return (result);
}

char	*ft_handle_heredoc(t_root *root, t_token *delim)
{
	t_heredoc_data	vars;

	vars.data = NULL;
	vars.end = false;
	vars.delim = delim->str;
	vars.expand = true;
	if (delim->state == SINGLE_Q)
		vars.expand = false;
	while (!vars.end)
	{
		vars.prompt = ft_set_heredoc_prompt();
		vars.input = readline(vars.prompt);
		free(vars.prompt);
		if (!vars.input)
			break ;
		ft_heredoc_do_checks(root, &vars);
	}
	free(delim->str);
	return (ft_heredoc_result_clean_up(vars.data));
}
