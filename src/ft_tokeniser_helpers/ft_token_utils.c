/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:20:11 by otodd             #+#    #+#             */
/*   Updated: 2024/07/07 22:30:55 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_type(t_token *token, int div)
{
	if (ft_strcmp(token->str, "") == 0 && div == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && div == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && div == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && div == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && div == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && div == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

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

int	ft_parsetokens(const char *input, int i, t_token **head)
{
	t_token	*token = NULL;
	char	tok_str[3] = {input[i], '\0', '\0'};

	if (input[i] == '>' && input[i + 1] == '>')
	{
		tok_str[1] = '>';
		tok_str[2] = '\0';
		i++;
	}
	token = ft_token_new(ft_strdup(tok_str));
	ft_token_add(head, token);
	return (i + 1);
}

int	ft_issep(char *input, int i)
{
	if (i > 0 && input[i - 1] == '\\' && ft_strchr("<>|;", input[i]))
		return (0);
	else if (ft_strchr("<>|;", input[i])) //add quotes checker
		return (1);
	else
		return (0);
}


