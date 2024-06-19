/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:19:20 by ssottori          #+#    #+#             */
/*   Updated: 2024/06/16 13:42:59 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>

void	config_siginit(void);
void	config_sigquit(void);
void	kill_shell(void);
void	ft_init_shell(t_root *root, int ac, char **av, char **env);

#endif

