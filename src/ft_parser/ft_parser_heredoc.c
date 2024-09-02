/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:12 by otodd             #+#    #+#             */
/*   Updated: 2024/09/02 16:33:45 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_heredoc_do_checks(t_root *root, t_heredoc_data *vars)
{
	if (ft_strcmp(vars->input, vars->delim) == 0)
	{
		free(vars->input);
		vars->end = true;
	}
	else
	{
		vars->data = ft_strarrayappend2(vars->data,
				ft_expand_str(root, vars->input));
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

char	*ft_handle_heredoc(t_root *root, char *delim)
{
	t_heredoc_data	vars;

	vars.data = NULL;
	vars.end = false;
	vars.delim = delim;
	while (!vars.end)
	{
		vars.prompt = ft_set_heredoc_prompt();
		vars.input = readline(vars.prompt);
		free(vars.prompt);
		if (!vars.input)
			break ;
		ft_heredoc_do_checks(root, &vars);
	}
	free(delim);
	return (ft_heredoc_result_clean_up(vars.data));
}
