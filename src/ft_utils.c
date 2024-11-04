/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:46:56 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/04 14:29:47 by otodd            ###   ########.fr       */
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

static char	*ft_generate_tmp_file(char *tmp, int lvl)
{
	char	*tmp_name;
	char	*n;
	char	*path;

	n = ft_itoa(lvl);
	tmp_name = ft_strjoin(tmp, n);
	free(n);
	path = ft_strjoin("/tmp/", tmp_name);
	free(tmp_name);
	return (path);
}

char	*ft_write_to_tmp(char *tmp, char *data, bool set_fd, int pipe_fd)
{
	int		fd;
	char	*path;
	int		lvl;

	lvl = 0;
	while (true)
	{
		path = ft_generate_tmp_file(tmp, lvl);
		if (!ft_isvalid_file_path(path))
			break ;
		free(path);
		lvl++;
	}
	if (!ft_create_file(path))
	{
		free(path);
		return (NULL);
	}
	fd = ft_file_fd(false, false, path);
	ft_putstr_fd(data, fd);
	close(fd);
	if (set_fd)
	{
		fd = ft_file_fd(false, true, path);
		if (dup2(fd, pipe_fd) == -1)
		{
			ft_fprintf(STDERR_FILENO, "error duping fd: %d -> %d: %s\n",
				fd, pipe_fd, strerror(errno));
			close(fd);
			free(path);
			return (NULL);
		}
	}
	return (path);
}

