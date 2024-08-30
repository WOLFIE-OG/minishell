/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_typers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:42:34 by otodd             #+#    #+#             */
/*   Updated: 2024/08/30 17:00:26 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_token_retype_check_type(t_token *token)
{
	if (token->next->type == ARG || token->next->type == PIPE
		|| token->next->type == TRUNC
		|| token->next->type == INPUT
		|| token->next->type == APPEND
		|| token->next->type == HEREDOC)
		return (true);
	return (false);
}

void	ft_token_retype(t_token *token)
{
	if (token->is_sep)
		return ;
	if (!token->prev)
	{
		if (token->next)
		{
			if (ft_token_retype_check_type(token))
				token->type = CMD;
		}
		else
			token->type = CMD;
	}
	else
	{
		if (token->prev->type == PIPE || token->prev->type == END
			|| token->prev->type == INPUT_FILE
			|| token->prev->type == OUTPUT_FILE)
		{
			if ((token->prev->prev && (token->prev->prev->type == INPUT
						|| token->prev->prev->type == TRUNC))
				&& (token->prev->prev->prev
					&& (token->prev->prev->prev->type == CMD
						|| token->prev->prev->prev->type == ARG
						|| token->prev->prev->prev->type == INPUT_FILE
						|| token->prev->prev->prev->type == OUTPUT_FILE)))
				token->type = ARG;
			else
				token->type = CMD;
		}
		else if (token->prev->type == TRUNC || token->prev->type == APPEND)
			token->type = OUTPUT_FILE;
		else if (token->prev->type == INPUT)
			token->type = INPUT_FILE;
		else if (token->prev->type == HEREDOC)
			token->type = HEREDOC_DELIM;
	}
}

void	ft_token_type(t_token *token, int div)
{
	token->is_sep = true;
	if (ft_strcmp(token->str, ">") == 0 && div == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && div == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0 && div == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "<") == 0 && div == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && div == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && div == 0)
		token->type = END;
	else
	{
		token->is_sep = false;
		token->type = ARG;
	}
}
