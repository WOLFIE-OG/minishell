/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:46:56 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/25 16:42:24 by otodd            ###   ########.fr       */
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