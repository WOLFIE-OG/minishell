/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:45 by otodd             #+#    #+#             */
/*   Updated: 2024/06/28 17:28:48 by otodd            ###   ########.fr       */
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
// # include <sys/ioctl.h>
# include <signal.h>

typedef struct s_root
{
	t_list	*env;
	char	**prompt;
	char	**p_head;
}	t_root;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


void	pwd(t_root *root);
void	cd(t_root *root, char *path);
void	export(t_root *root, char *data);
void	echo(t_root *root, char **data);



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



void		config_siginit(void);
void		config_sigquit(void);
void		kill_shell(void);
void		ft_init_shell(t_root *root, int ac, char **av, char **env);

//I suggest making separate .h files for the builtins,
//the parser, the lexer and execution etc

# define SUCCESS 0

// # define RESET "\033[0;39m"
// # define GRAY "\033[0;90m"
// # define RED "\033[0;91m"
// # define GREEN "\033[0;92m"
// # define YELLOW "\033[0;93m"
// # define BLUE "\033[0;94m"
// # define MAGENTA "\033[0;95m"
// # define CYAN "\033[0;96m"
// # define WHITE "\033[0;97m"

extern int  g_var_signal;

#endif
