/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:47:10 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/30 00:12:28 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_find_token_by_index(t_root *root, int index)
{
	t_token	*head;

	head = root->tokens;
	while (head)
	{
		if (head->index == index)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	ft_token_retype(t_token *token)
{
	if (!token->prev)
	{
		if (token->next)
		{
			if (token->next->type == ARG || token->next->type == PIPE)
				token->type = CMD;
		}
		else
			token->type = CMD;
	}
	else
		if (token->prev->type == PIPE
			|| token->prev->type == END)
			token->type = CMD;
	else if (token->prev->type == INPUT
		|| token->prev->type == TRUNC
		|| token->prev->type == APPEND)
		token->type = INPUT_FILE;
}

void	ft_token_type(t_token *token, int div)
{
	if (ft_strcmp(token->str, ">") == 0 && div == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && div == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && div == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && div == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && div == 0)
		token->type = END;
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

t_token	*ft_get_token_by_type_at_i(t_token *tkns, t_token_type type, int index)
{
	t_token	*head;

	head = tkns;
	while (head)
	{
		if (head->type == type && head->index == index)
			return (head);
		head = head->next;
	}
	return (NULL);
}
