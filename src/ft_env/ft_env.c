/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:16:12 by otodd             #+#    #+#             */
/*   Updated: 2024/07/18 16:35:31 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_init_env(char **envp)
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

char	**ft_env_to_array(t_root *root)
{
	t_list		*head;
	t_env_var	*var;
	char		*str;
	char		**tmp;
	static char	**str_env = NULL;

	head = root->env;
	while (head)
	{
		var = (t_env_var *)head->content;
		tmp = ft_strarrayappend2(NULL, ft_strdup(var->key));
		tmp = ft_strarrayappend2(tmp, ft_strdup("="));
		tmp = ft_strarrayappend2(tmp, ft_strdup(var->value));
		str = ft_strarraytostr(tmp);
		ft_free_array(tmp, ft_strarraylen(tmp));
		free(tmp);
		str_env = ft_strarrayappend2(str_env, ft_strdup(str));
		free(str);
		head = head->next;
	}
	return (str_env);
}

static void	ft_free_var(void *node)
{
	t_env_var	*var;

	var = (t_env_var *)node;
	//ft_printf("Free'd: %s\n", var->key);
	free(var->key);
	free(var->value);
}

void	ft_free_env(t_root *root)
{
	ft_lstiter(root->env, ft_free_var);
	ft_lstclear(&root->env, free);
	free(root->env);
}
