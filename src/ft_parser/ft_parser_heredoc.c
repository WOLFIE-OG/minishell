/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:21:12 by otodd             #+#    #+#             */
/*   Updated: 2024/11/07 15:18:21 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_heredoc_do_checks(t_root *root, t_heredoc_data *vars)
{
	char	*str;

	if (ft_strcmp(vars->input, vars->delim) == 0)
	{
		vars->end = true;
		free(vars->input);
	}
	else
	{
		if (vars->expand)
			str = ft_expand_str(root, vars->input, false);
		else
		{
			str = ft_strdup(vars->input);
			free(vars->input);
		}
		vars->data = ft_strarrayappend2(vars->data, str);
		vars->data = ft_strarrayappend2(vars->data, ft_strdup("\n"));
	}
}

static char	*ft_heredoc_result_clean_up(char **data)
{
	char	*result;
	char	*tmp;

	result = ft_strarraytostr(data);
	if (!result)
		result = ft_strdup("\0");
	ft_gc_str_array(data);
	tmp = ft_write_to_tmp("minishell_tmp_heredoc", result, false, 0);
	free(result);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static void	ft_join_heredoc_compounds(t_token **head_t, bool *expand)
{
	t_token	*c_head_t;
	t_token	*next_token;
	char	*tmp;

	c_head_t = *head_t;
	while (*head_t && (*head_t)->is_compound
		&& (*head_t)->type == HEREDOC_DELIM)
	{
		if (*head_t == c_head_t)
		{
			*head_t = (*head_t)->next;
			continue ;
		}
		if ((*head_t)->state == SINGLE_Q && expand)
			*expand = false;
		tmp = ft_strjoin(c_head_t->str, (*head_t)->str);
		free(c_head_t->str);
		c_head_t->str = tmp;
		next_token = (*head_t)->next;
		ft_token_delone(ft_token_pop(*head_t), free);
		*head_t = next_token;
	}
	c_head_t->is_compound = false;
	*head_t = c_head_t;
}

char	*ft_handle_heredoc(t_root *root, t_token *delim)
{
	t_heredoc_data	vars;

	vars.data = NULL;
	vars.end = false;
	vars.expand = true;
	ft_join_heredoc_compounds(&delim, &vars.expand);
	vars.delim = delim->str;
	while (!vars.end)
	{
		vars.prompt = ft_set_heredoc_prompt();
		vars.input = readline(vars.prompt);
		free(vars.prompt);
		if (!vars.input)
			break ;
		ft_heredoc_do_checks(root, &vars);
	}
	free(delim->str);
	return (ft_heredoc_result_clean_up(vars.data));
}
