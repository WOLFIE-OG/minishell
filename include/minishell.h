/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:45 by otodd             #+#    #+#             */
/*   Updated: 2024/08/02 18:05:38 by otodd            ###   ########.fr       */
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
	END,
	INPUT_FILE
}	t_token_type;

extern int	g_var_signal;

// This is the main data struct of the shell
typedef struct s_cmd
{
	t_token_type	post_action;
	struct s_token	*cmd_tokens;
	int				pipe[2];
	bool			is_builtin;
	bool			execute;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_root
{
	t_list			*env;
	struct s_token	*ctx_tokens;
	struct s_cmd	*preped_cmds;
	char			**builtin_array;
	char			**prompt;
	char			*init_args;
	char			*shell_name;
	int				prev_cmd_status;
	struct s_cmd	*prev_cmd;
	struct s_cmd	*current_cmd;
}	t_root;

typedef struct s_token
{
	int				index;
	char			*str;
	t_token_type	type;
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

// src/ft_env/ft_env.c - Env

t_list		*ft_init_env(char **envp);
char		**ft_env_to_array(t_root *root);
void		ft_free_env(t_root *root);

// src/ft_env/ft_env_helpers.c - Env helpers

t_env_var	*ft_find_var_by_key(t_root *root, char *key);
t_env_var	*ft_set_var(t_root *root, char *key, char *value);
t_env_var	*ft_get_var(t_root *root, char *key);
t_list		*ft_find_node_by_var_key(t_root *root, char *key);
bool		ft_unset_var(t_root *root, char *key);

// src/ft_signals.c - Signal handler

void		ft_config_sigint(void);
void		ft_config_sigint_cmd(void);

// src/ft_executor/ft_executor_builtins.c - Executor builtin functions

void		ft_builtins(t_root *root);

// src/ft_executor/ft_executor_io.c - Executor I/O functions

void		ft_cmd_output(t_root *root);
void		ft_cmd_trunc_append(t_root *root);
char		*ft_fd_to_str(int fd);
bool		ft_write_to_file(char *data, bool append, char *path);
char		*ft_read_from_file(char *path);

// src/ft_executor/ft_executor_redirs.c - Executor redir

bool		ft_handle_worker_pipes(t_root *root);

// src/ft_executor/ft_executor_utils.c - Executor utils

bool		ft_is_builtin(t_root *root, char *cmd);
char		**ft_worker_arg_str(t_root *root);
char		*ft_cmd_path(t_root *root, char *cmd);
bool		ft_is_path_valid(char *path, bool check_exec, bool check_read);

// src/ft_executor/ft_executor_worker_launcher.c - Executor worker launcher

void		ft_worker_launcher(t_root *root);

// src/ft_executor/ft_executor_worker.c - Executor worker functions

void		ft_worker(t_root *root, char *cmd, char **args);

// src/ft_executor/ft_executor.c - Executor functions

void		ft_executor(t_root *root);

// src/ft_gc/ft_executor_gc.c - Garbage executor functions

void		ft_gc_str_array(char **arr);
void		ft_gc_shell(t_root *root);

// src/ft_gc/ft_general_gc.c - Garbage general functions

void		ft_gc_preped_cmds(t_root *root);

// src/ft_gc/ft_tokeniser_gc.c - Garbage tokeniser functions

void		ft_gc_tokens(t_token *head);

// src/ft_parser/ft_*.c - Parser stuff

t_cmd		*ft_new_cmd(void);
void		ft_parser_check_for_input(t_root *root, t_token **token);
bool		ft_parser_adjust_tokens(t_root *root);
t_cmd		*ft_parser(t_root *root);

// src/ft_tokeniser_helpers/ft_token_*.c - Tonkeniser helper functions

void		ft_token_add(t_token **lst, t_token *new_l);
void		ft_token_clear(t_token **lst, void (*del)(void *));
void		ft_token_delone(t_token *lst, void (*del)(void *));
t_token		*ft_token_last(t_token *lst);
t_token		*ft_token_new(char *str);
t_token		*ft_token_dup(t_token *token);
t_token		*ft_token_pop(t_token *node);
size_t		ft_token_size(t_token *lst);
void		ft_token_reindex(t_token *token);
void		ft_token_type(t_token *token, int div);
void		ft_token_retype(t_token *token);
t_token		*ft_find_token_by_index(t_token *tokens, int index);
t_state		ft_handle_state(char c, t_state current_state);
int			ft_unclosed_quote(char *str);
t_token		*ft_get_token_by_type_at_i(t_token *tkns,
				t_token_type type, int index);
void		ft_token_move_before(t_token *move_token, t_token *target);

// src/ft_errs.c - Error functions

void		ft_print_err(const char *message);

// src/ft_init.c - Init functions

void		ft_init_shell(t_root *root, int ac, char **av, char **env);

// src/ft_lexer.c - Lexer functions

void		ft_test_token(void);
t_token		*ft_tokenizer(char *input);
int			ft_process_tokens(char *input,
				t_token **head, t_state *state, int start);
int			ft_issep(char *input, int i);
int			ft_skip_whitespace(const char *input, int i);
char		*ft_tokenstr(const char *input, int start, int end);
int			ft_parse_tokens(const char *input, int i, t_token **head);

// src/ft_utils - General Utils

char		*ft_set_prompt(t_root *root);

// src/ft_tests.c - Test functions

int			tokenizer_tester(int ac, char **av);
void		print_tokens(t_token *head);

#endif