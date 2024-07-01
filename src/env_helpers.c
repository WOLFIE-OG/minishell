/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:16:12 by otodd             #+#    #+#             */
/*   Updated: 2024/07/01 16:18:53 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_var	*set_var(t_root *root, char *key, char *value)
{
	t_env_var	*var;

	var = find_var_by_key(root, key);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
		free(value);
		return (var);
	}
	else
	{
		var = malloc(sizeof(t_env_var));
		var->key = ft_strdup(key);
		var->value = ft_strdup(value);
		free(value);
		ft_lstadd_back(&root->env, ft_lstnew(var));
		return (var);
	}
}

bool	unset_var(t_root *root, char *key)
{
	t_list		*node;
	t_env_var	*var;

	node = find_node_by_var_key(root, key);
	if (node)
	{
		node = ft_lstpop(node);
		var = (t_env_var *)node->content;
		printf("%s\n", var->key);
		free(var->value);
		free(var->key);
		free(var);
		free(node);
		return (true);
	}
	return (false);
}

t_env_var	*get_var(t_root *root, char *key)
{
	return (find_var_by_key(root, key));
}

t_env_var	*find_var_by_key(t_root *root, char *key)
{
	t_list		*head;
	t_env_var	*var;

	head = root->env;
	while (head)
	{
		var = (t_env_var *)head->content;
		if (!ft_strcmp(var->key, key))
			return ((t_env_var *)head->content);
		head = head->next;
	}
	return (NULL);
}

t_list	*find_node_by_var_key(t_root *root, char *key)
{
	t_list		*head;
	t_env_var	*var;

	head = root->env;
	while (head)
	{
		var = (t_env_var *)head->content;
		if (!ft_strcmp(var->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}
