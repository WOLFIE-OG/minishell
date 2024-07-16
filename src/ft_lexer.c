/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:15:41 by otodd             #+#    #+#             */
/*   Updated: 2024/07/16 16:15:25 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
parse input string and convert to linked list of tokens 
each token should correspond to a type*/

t_token	*ft_tokenizer(char *input)
{
	t_token	*head = NULL;
	t_token	*token;
	int		i;
	char	*tok_str;
	int		start;

	i = 0;
	while (input[i])
	{
		i = ft_skip_whitespace(input, i);
		start = i;
		while (!ft_iswhitespace(input[i]) && !ft_issep(input, i))
			i++;
		if (start != i)
		{
			tok_str = ft_tokenstr(input, start, i);
			// if (!ft_strcmp(tok_str, ""))
			// 	break ;
			token = ft_token_new(tok_str);
			ft_token_type(token, 0);
			ft_token_add(&head, token);
			if (!input[i])
				continue ;
		}
		if (ft_issep(input, i)) //  should i ignore separators?
			i = ft_parsetokens(input, i, &head);
		else
			i++;
	}
	return (head);
}

void	ft_test_token(void)
{
	char *testtokens[] = {"", ">", ">>", "<", "|", ";", "cmd", "arg"};
	int num_tests = sizeof(testtokens) / sizeof(testtokens[0]);

		for (int i = 0; i < num_tests; i++)
		{
			t_token *token = ft_token_new(ft_strdup(testtokens[i]));
			ft_token_type(token, 0);

			printf("Token value: '%s' -> Token type: %d\n", token->str, token->type);

			free(token->str);
			free(token);
		}
}
