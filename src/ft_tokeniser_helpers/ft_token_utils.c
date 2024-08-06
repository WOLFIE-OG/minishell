/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:47:10 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/06 12:43:34 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_skip_whitespace(const char *input, int i)
{
	while (input[i] && ft_iswhitespace(input[i]))
		i++;
	return (i);
}

/* Extract a substr from the input str to create the token str */
char	*ft_tokenstr(const char *input, int start, int end)
{
	return (ft_substr(input, start, end - start));
}

int	ft_parse_tokens(const char *input, int i, t_token **head)
{
	t_token	*token;
	char	tok_str[3];

	tok_str[0] = input[i];
	tok_str[1] = '\0';
	tok_str[2] = '\0';
	token = NULL;
	if (input[i] == '>' && input[i + 1] == '>')
	{
		tok_str[1] = '>';
		tok_str[2] = '\0';
		i++;
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		tok_str[1] = '<';
		tok_str[2] = '\0';
		i++;
	}
	token = ft_token_new(ft_strdup(tok_str));
	ft_token_add(head, token);
	return (i + 1);
}

/* add quotes checker */
int	ft_issep(char *input, int i)
{
	if (i > 0 && input[i - 1] == '\\' && ft_strchr("<>|;", input[i]))
		return (0);
	else if (ft_strchr("<>|;", input[i]))
		return (1);
	else
		return (0);
}
