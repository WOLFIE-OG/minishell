/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:45 by otodd             #+#    #+#             */
/*   Updated: 2024/07/16 17:30:29 by otodd            ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <signal.h>

typedef enum e_token_type
{
	EMPTY, 
	CMD,
	ARG,
	TRUNC, // >
	APPEND, // >>
	INPUT, // <
	PIPE, // |
	END // ;
}	t_token_type;

extern int	g_var_signal;
// This is the main data struct of the shell
typedef struct s_root
{
	t_list			*env;
	struct s_token	*tokens;
	char			**builtin_array;
	char			**prompt;
	char			*args;
	char			*name;
}	t_root;

typedef struct s_token
{
	int				index;
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

// src/ft_builtins/ft_*.c - Bultins

void		ft_pwd(t_root *root);
int			ft_cd(t_root *root);
void		ft_export(t_root *root);
void		ft_echo(t_root *root);
void		ft_unset(t_root *root);
void		ft_env(t_root *root);
void		ft_exit(t_root *root, int code);

// src/ft_tokeniser_helpers/ft_*.c - Tonkeniser Helper Functions

void		ft_token_add(t_token **lst, t_token *new_l);
void		ft_token_clear(t_token **lst, void (*del)(void *));
void		ft_token_delone(t_token *lst, void (*del)(void *));
t_token		*ft_token_last(t_token *lst);
t_token		*ft_token_new(char *str);
t_token		*ft_token_pop(t_token *node);
size_t		ft_token_size(t_token *lst);
void		ft_token_type(t_token *token, int div);
t_token		*ft_find_token_by_index(t_root *root, int index);


// src/ft_env.c - Env

t_list		*ft_init_env(char **envp);
char		**ft_env_to_array(t_root *root);
void		ft_free_env(t_root *root);

// src/ft_env_helpers.c - Env Helpers

t_env_var	*ft_find_var_by_key(t_root *root, char *key);
t_env_var	*ft_set_var(t_root *root, char *key, char *value);
t_env_var	*ft_get_var(t_root *root, char *key);
t_list		*ft_find_node_by_var_key(t_root *root, char *key);
bool		ft_unset_var(t_root *root, char *key);

// src/ft_kill.c - Shell kill

void		ft_config_siginit(void);
void		ft_config_sigquit(void);
void		ft_kill_shell(t_root *root, int code);
void		ft_init_shell(t_root *root, int ac, char **av, char **env);

// src/ft_executor.c - Executor Functions

bool		ft_is_builtin(t_root *root, char *cmd);
void		ft_runner_process(t_root *root, char **args);

// src/ft_lexer.c - Lexer

void		ft_test_token(void);
t_token		*ft_tokenizer(char *input);
int			ft_issep(char *input, int i);
int			ft_skip_whitespace(const char *input, int i);
char		*ft_tokenstr(const char *input, int start, int end);
int			ft_parsetokens(const char *input, int i, t_token **head);

# define SUCCESS 0

#endif