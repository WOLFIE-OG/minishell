/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:12 by otodd             #+#    #+#             */
/*   Updated: 2024/08/06 17:23:41 by otodd            ###   ########.fr       */
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

static void	ft_heredoc_do_checks(
	char *input, char *delim, char ***data, bool *end)
{
	char	*match;

	match = ft_strnstr(input, delim, ft_strlen(input));
	if (match)
	{
		if (ft_heredoc_start_end_check(input, delim)
			|| ft_heredoc_whitespace_check(input, match, delim))
			*data = ft_strarrayappend2(*data,
					ft_substr(input, 0, match - input));
		*end = true;
	}
	else
	{
		*data = ft_strarrayappend2(*data, ft_strdup(input));
		*data = ft_strarrayappend2(*data, ft_strdup("\n"));
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

char	*ft_handle_heredoc(char *delim)
{
	char	*input;
	char	**data;
	char	*prompt;
	bool	end;

	data = NULL;
	end = false;
	while (!end)
	{
		prompt = ft_set_heredoc_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		ft_heredoc_do_checks(input, delim, &data, &end);
		free(input);
	}
	free(delim);
	return (ft_heredoc_result_clean_up(data));
}
