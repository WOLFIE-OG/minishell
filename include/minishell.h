/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:45 by otodd             #+#    #+#             */
/*   Updated: 2024/07/25 18:06:39 by otodd            ###   ########.fr       */
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
# define SUCCESS 0

typedef enum e_state
{
	NORMAL,
	SINGLE_Q,
	DOUBLE_Q,
}	t_state;
/*
	EMPTY, 
	CMD,
	ARG,
	TRUNC, // >
	APPEND, // >>
	INPUT, // <
	PIPE, // |
	END // ;
*/
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
}	t_token_type;

extern int	g_var_signal;
// This is the main data struct of the shell
typedef struct s_cmd
{
	int				post_action;
	struct s_token	*cmd_tokens;
	int				io_out[2];
	struct s_cmd	*next;
}	t_cmd;
typedef struct s_root
{
	t_list			*env;
	struct s_token	*tokens;
	struct s_cmd	*cmds;
	char			**builtin_array;
	char			**prompt;
	char			*args;
	char			*name;
	int				last_return_code;
	struct s_cmd	*last_executed_cmd;
	struct s_cmd	*current_cmd;
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

int			ft_pwd(t_root *root);
int			ft_cd(t_root *root);
int			ft_export(t_root *root);
int			ft_echo(t_root *root);
int			ft_unset(t_root *root);
int			ft_env(t_root *root);
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
void		ft_token_retype(t_token *token);
t_token		*ft_find_token_by_index(t_root *root, int index);
t_state		ft_handle_state(char c, t_state current_state);

// src/ft_env/ft_env.c - Env

t_list		*ft_init_env(char **envp);
char		**ft_env_to_array(t_root *root);
void		ft_free_env(t_root *root);

// src/ft_env/ft_env_helpers.c - Env Helpers

t_env_var	*ft_find_var_by_key(t_root *root, char *key);
t_env_var	*ft_set_var(t_root *root, char *key, char *value);
t_env_var	*ft_get_var(t_root *root, char *key);
t_list		*ft_find_node_by_var_key(t_root *root, char *key);
bool		ft_unset_var(t_root *root, char *key);

// src/ft_signals.c - Signal handler

void		ft_config_siginit(void);
void		ft_config_sigquit(void);

// src/ft_executor/ft_executor.c - Executor Functions

int			ft_executor(t_root *root, t_cmd *cmds);

// src/ft_executor/ft_executor_helpers.c = Executor Helper Functions

bool		ft_is_builtin(t_root *root, char *cmd);
bool		ft_handle_worker_pipes(t_root *root);
char		*ft_build_pipe_output(int fd);

// src/ft_lexer.c - Lexer

void		ft_test_token(void);
t_token		*ft_tokenizer(char *input);
int			ft_process_tokens(char *input,
				t_token **head, t_state *state, int start);
int			ft_issep(char *input, int i);
int			ft_skip_whitespace(const char *input, int i);
char		*ft_tokenstr(const char *input, int start, int end);
int			ft_parse_tokens(const char *input, int i, t_token **head);

// src/ft_gc/ft_general_gc.c - General garbage collection functions

void		ft_gc_str_array(char **arr);
void		ft_gc_tokens(t_token *head);
void		ft_gc_shell(t_root *root);

// src/ft_init.c - Init functions

void		ft_init_shell(t_root *root, int ac, char **av, char **env);

// src/ft_utils - General Utils

char		*ft_set_prompt(t_root *root);



// src/ft_tests.c - Test functions

int			tokenizer_tester(int ac, char **av);
void		print_tokens(t_token *head);

#endif