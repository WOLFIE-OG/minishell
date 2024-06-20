/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:16:12 by otodd             #+#    #+#             */
/*   Updated: 2024/06/20 16:42:31 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	set_var(t_root *root, char *key, char *value)
{
	t_env_var	*var;

	var = find_var_by_key(root, key);
	if (var)
	{
		var->value = ft_strdup(value);
		free(value);
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

t_list	*init_env(char **envp)
{
	char		**temp;
	t_list		*env;
	t_list		*head;
	t_env_var	*var;

	env = NULL;
	while (*envp)
	{
		temp = ft_key_value(*envp, '=');
		var = malloc(sizeof(t_env_var));
		var->key = ft_strdup(temp[0]);
		var->value = ft_strdup(temp[1]);
		if (!env)
		{
			env = ft_lstnew(var);
			head = env;
		}
		else
			ft_lstadd_back(&env, ft_lstnew(var));
		ft_free_array(temp, ft_strarraylen(temp));
		free(temp);
		envp++;
	}
	return (head);
}