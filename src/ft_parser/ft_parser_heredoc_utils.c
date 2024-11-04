/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:12 by otodd             #+#    #+#             */
/*   Updated: 2024/11/04 16:24:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_set_heredoc_prompt(void)
{
	char	**prompt;
	char	*prompt2;

	prompt = ft_strarrayappend2(NULL, ft_strdup(BBLU));
	prompt = ft_strarrayappend2(prompt, ft_strdup("heredoc"));
	prompt = ft_strarrayappend2(prompt, ft_strdup(RESET));
	prompt = ft_strarrayappend2(prompt, ft_strdup("> "));
	prompt2 = ft_strarraytostr(prompt);
	ft_gc_str_array(prompt);
	return (prompt2);
}