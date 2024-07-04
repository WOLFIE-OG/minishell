/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:15:41 by otodd             #+#    #+#             */
/*   Updated: 2024/07/04 17:32:16 by otodd            ###   ########.fr       */
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

t_token	*ft_tokenizer(t_token value, char *input)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	(void)w;
	(void)i;
	(void)value;

	while (!ft_iswhitespace(input[i++]))
	{

	}
	return (NULL);
}

void	ft_test_token(void)
{
	char *testtokens[] = {"", ">", ">>", "<", "|", ";", "cmd", "arg"};
	int num_tests = sizeof(testtokens) / sizeof(testtokens[0]);

		for (int i = 0; i < num_tests; i++)
		{
			t_token *token = ft_token_new(testtokens[i]);
			ft_token_type(token, 0);

			printf("Token value: '%s' -> Token type: %d\n", token->str, token->type);

			free(token->str);
			free(token);
		}
} 
