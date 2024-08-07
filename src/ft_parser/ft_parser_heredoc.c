/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:12 by otodd             #+#    #+#             */
/*   Updated: 2024/08/07 15:37:08 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_heredoc_whitespace_check(char *input, char *match, char *delim)
{
	if (ft_iswhitespace(input[(match - input) - 1])
		&& ft_iswhitespace(input[(match - input) + ft_strlen(delim)]))
		return (true);
	return (false);
}

static bool	ft_heredoc_start_end_check(char *input, char *delim)
{
	int	len_delim;
	int	len_input;

	len_delim = ft_strlen(delim);
	len_input = ft_strlen(input);
	if ((ft_strcmp(input, delim) == 0)
		|| (ft_strcmp(&input[len_input - len_delim], delim) == 0
			&& ft_iswhitespace(input[(len_input - len_delim) - 1])))
		return (true);
	return (false);
}

static void	ft_heredoc_do_checks(t_root *root, t_heredoc_data *vars)
{
	char	*match;

	match = ft_strnstr(vars->input, vars->delim, ft_strlen(vars->input));
	if (match)
	{
		if (ft_heredoc_start_end_check(vars->input, vars->delim)
			|| ft_heredoc_whitespace_check(vars->input, match, vars->delim))
			vars->data = ft_strarrayappend2(vars->data,
					ft_substr(vars->input, 0, match - vars->input));
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
