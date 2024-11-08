/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:46:56 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/08 16:24:34 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_format_pwd_get_home(t_root *root, char **home_str)
{
	t_env_var	*home;

	home = ft_get_var(root, "HOME");
	if (!home)
		*home_str = "(null)";
	else
		*home_str = home->value;
}

static char	*ft_format_pwd(t_root *root)
{
	char		*str;
	char		*home_str;
	char		*str_join;
	t_env_var	*pwd;

	pwd = ft_get_var(root, "PWD");
	if (pwd)
	{
		ft_format_pwd_get_home(root, &home_str);
		str = ft_substr(pwd->value, 0, ft_strlen(home_str));
		if (ft_strcmp(str, home_str) == 0)
		{
			str_join = ft_strjoin("~", &pwd->value[ft_strlen(home_str)]);
			free(str);
			str = ft_strdup(str_join);
			free(str_join);
			return (str);
		}
		if (str)
			free(str);
		return (ft_strdup(pwd->value));
	}
	return (ft_strdup("(null)"));
}

char	*ft_set_prompt(t_root *root)
{
	const t_env_var	*user = ft_get_var(root, "USER");

	root->prompt = ft_strarrayappend2(NULL, ft_strdup(BGRN));
	if (user)
		root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(user->value));
	else
		root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("user"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("@"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("minishell:"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(BBLU));
	root->prompt = ft_strarrayappend2(root->prompt, ft_format_pwd(root));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("$ "));
	return (ft_strarraytostr(root->prompt));
}

bool	ft_has_cmd(t_token *head)
{
	while (head)
	{
		if (head->type == CMD)
			return (true);
		head = head->prev;
	}
	return (false);
}
