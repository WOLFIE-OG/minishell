/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:15:41 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 14:09:32 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Start
 |
 V
Read Input Line
 |
 V
Is Space? ------ No
 |               |
Yes             |
 |               V
Skip Spaces     Is '|' or '&' or '<' or '>' or '(' or ')' --- No
 |               |                                           |
Tokenize Space   |                                           V
				 Tokenize Operator                        Tokenize Command*//* 
Start
 |
 V
Read Input Line
 |
 V
Is Space? ------ No
 |               |
Yes             |
 |               V
Skip Spaces     Is '|' or '&' or '<' or '>' or '(' or ')' --- No
 |               |                                           |
Tokenize Space   |                                           V
				 Tokenize Operator                        Tokenize Command
*/

#include "../include/minishell.h"

t_token	*add_new(char *value)
{
	t_token = malloc(sizeof(t_token));

	if (!token)
		return NULL;

	token->value = ft_strdup(value);
	token->type = EMPTY;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	tokenizer(t_token value, char *input)
{
	int i;
	int w;

	i = 0;
	w = 0;

	while (!ft_iswhitespace(input[i++]))
	{

	}
}

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
		token-> = CMD;
	else
		token->type = ARG;
}

void	test_token()
{
	char *testtokens[] = {"", ">", ">>", "<", "|", ";", "cmd", "arg"};
	int num_tests = sizeof(testtokens) / sizeof(testtokens[0]);

		for (int i = 0; i < num_tests; i++)
		{
			t_token *token = add_new(testtokens[i]);
			ft_token_type(token, 0);

			printf("Token value: '%s' -> Token type: %d\n", token->value, token->type);

			free(token->value);
			free(token);
		}
} 
