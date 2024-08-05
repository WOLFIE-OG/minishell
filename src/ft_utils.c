/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:46:56 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/05 18:18:01 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_skip_space(char *input, int i)
{
	int	j;

	j = 0;
	while (ft_iswhitespace(input[i + j]))
		j++;
	return (j);
}

char	*ft_set_prompt(t_root *root)
{
	root->prompt = ft_strarrayappend2(NULL, ft_strdup(BGRN));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(ft_get_var(root, "USER")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("@"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("minishell:"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(BBLU));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(ft_get_var(root, "PWD")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("$ "));
	return (ft_strarraytostr(root->prompt));
}

static char	*ft_set_heredoc_prompt(void)
{
	char	**prompt;
	char	*prompt2;

	prompt = ft_strarrayappend2(NULL, ft_strdup(BBLU));
	prompt = ft_strarrayappend2(prompt, ft_strdup("heredoc"));
	prompt = ft_strarrayappend2(prompt, ft_strdup(RESET));
	prompt = ft_strarrayappend2(prompt, ft_strdup("$ "));
	prompt2 = ft_strarraytostr(prompt);
	ft_gc_str_array(prompt);
	return (prompt2);
}

char	*ft_handle_heredoc(char *delim)
{
	bool	end;
	char	*input;
	char	*prompt;
	char	**data;
	char	*match;

	end = false;
	data = NULL;
	while (!end)
	{
		prompt = ft_set_heredoc_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		match = ft_strnstr(input, delim, ft_strlen(input));
		if (match)
		{
			if ((ft_strcmp(input, delim) == 0
					|| ft_strcmp(&input[ft_strlen(input) - ft_strlen(delim)],
						delim) == 0)
				|| (ft_iswhitespace(input[(match - input) - 1])
					&& ft_iswhitespace(input[(match - input)
							+ ft_strlen(delim)])))
				data = ft_strarrayappend2(data,
						ft_substr(input, 0, match - input));
			end = true;
		}
		else
			data = ft_strarrayappend2(data, ft_strdup(input));
		free(input);
	}
	return (ft_strarraytostr(data));
}
