/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:18:27 by otodd             #+#    #+#             */
/*   Updated: 2024/06/24 14:44:59 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

t_list		*init_env(char **envp);
t_env_var	*find_var_by_key(t_root *root, char *key);
t_env_var	*set_var(t_root *root, char *key, char *value);
t_env_var	*get_var(t_root *root, char *key);
void		free_env_list(t_root *root);

#endif