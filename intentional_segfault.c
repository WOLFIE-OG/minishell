/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intentional_segfault.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:12:56 by otodd             #+#    #+#             */
/*   Updated: 2024/08/06 19:20:23 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wait.h>

int	main(void)
{
	kill(getpid(), SIGSEGV);
	return (0);
}
