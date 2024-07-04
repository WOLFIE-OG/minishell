/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:45 by otodd             #+#    #+#             */
/*   Updated: 2024/07/02 16:36:00 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/include/libft.h"
//# include <csignal.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
// # include <sys/ioctl.h>
# include <signal.h>

typedef enum e_token_type
{
	EMPTY,
	CMD,
	ARG,
	TRUNC,
	APPEND,
	INPUT,
	PIPE,
	END
} t_token_type;

extern int	g_var_signal;
// This is the main data struct of the shell
typedef struct s_root
{
	t_list	*env;
	char	**builtin_array;
	char	**prompt;
	char	*args;
	char	*name;
}	t_root;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* These are the environment variables of the shell stored
via a bi-directional linked list*/
typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

// src/builtins/*.c - Bultins

void		ft_pwd(t_root *root);
int			ft_cd(t_root *root, char *path);
void		ft_export(t_root *root, char *data);
void		ft_echo(char **data);
void		ft_unset(t_root *root, char *key);
void		ft_env(t_root *root);
void		ft_exit(t_root *root, int code);

// src/env.c - Env

t_list		*init_env(char **envp);
char		**env_to_array(t_root *root);
void		free_env(t_root *root);

// src/env_helpers.c - Env Helpers

t_env_var	*find_var_by_key(t_root *root, char *key);
t_env_var	*set_var(t_root *root, char *key, char *value);
t_env_var	*get_var(t_root *root, char *key);
t_list		*find_node_by_var_key(t_root *root, char *key);
bool		unset_var(t_root *root, char *key);

// src/kill.c - Shell kill

void		config_siginit(void);
void		config_sigquit(void);
void		kill_shell(t_root *root, int code);
void		ft_init_shell(t_root *root, int ac, char **av, char **env);

// src/executor.c - Executor Functions

bool		is_builtin(t_root *root, char *cmd);
void		runner_process(t_root *root, char **args);

void	test_token()
void	ft_token_type(t_token *token, int div);

# define SUCCESS 0

#endif
