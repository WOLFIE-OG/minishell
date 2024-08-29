/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:46:56 by ssottori          #+#    #+#             */
/*   Updated: 2024/08/29 17:10:25 by otodd            ###   ########.fr       */
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

static char	*ft_format_pwd(t_root *root)
{
	char	*str;
	char	*str_join;
	t_env_var	*pwd;
	t_env_var	*home;

	pwd = ft_get_var(root, "PWD");
	if (pwd)
	{
		home = ft_get_var(root, "HOME");
		str = ft_substr(pwd->value, 0, ft_strlen(home->value));
		if (ft_strcmp(str, home->value) == 0)
		{
			str_join = ft_strjoin("~", &pwd->value[ft_strlen(home->value)]);
			free(str);
			str = ft_strdup(str_join);
			free(str_join);
			return (str);
		}
		return (ft_strdup(pwd->value));
	}
	return (ft_strdup("(null)"));
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
	root->prompt = ft_strarrayappend2(root->prompt, ft_format_pwd(root));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("$ "));
	return (ft_strarraytostr(root->prompt));
}

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

char	*ft_trim_start_end(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*new_string;

	if (!s1)
		return (NULL);
	start = 0;
	if (ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	if (ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	new_string = ft_substr(s1, start, len);
	if (!new_string)
		return (NULL);
	new_string[len] = '\0';
	return (new_string);
}

int	ft_is_dir(char *path)
{
	struct stat	pth;

	if (stat(path, &pth) != 0)
		return (-1);
	if (S_ISDIR(pth.st_mode))
	{
		errno = EISDIR;
		return (true);
	}
	return (false);
}
