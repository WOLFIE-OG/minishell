/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:25:07 by otodd             #+#    #+#             */
/*   Updated: 2024/06/26 13:33:53 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	pwd(t_root *root);
void	cd(t_root *root, char *path);
void	export(t_root *root, char *data);
void	echo(t_root *root, char **data);

#endif