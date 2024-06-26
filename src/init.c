/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/06/25 13:46:59 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int arg_n, char **arg_a, char *envp[])
{
	(void)arg_n;
	(void)arg_a;
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

	while (env)
	{
		var = (t_env_var *)env->content;
		ft_printf("Key: %s | Value: %s\n", var->key, var->value);
		free(var->key);
		free(var->value);
		env = env->next;
	}
	ft_lstclear(&head, free);
	free(head);
	return (EXIT_SUCCESS);
}
