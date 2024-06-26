/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:45 by otodd             #+#    #+#             */
/*   Updated: 2024/06/25 14:27:18 by otodd            ###   ########.fr       */
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
# include <signal.h>

typedef struct s_root
{
	t_list	*env;
	char	**prompt;
	char	**p_head;
}	t_root;

# include "parser.h"
# include "env.h"
# include "builtins.h"

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
