/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:16:12 by otodd             #+#    #+#             */
/*   Updated: 2024/06/18 13:50:30 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_env(char **envp)
{
	int	i;

	// we cant use strtok but we can implement it
	// aim is to get KEY=VALUE into a env struct for example
	// USER=wolfie becomes
	/*
	EnvVar data

	data.name = "USER"
	data.value = "wolfie"

	This will be a big array of EnvVar's
	*/
	printf("%s\n", strtok(envp[58], "="));
	i = 0;
	while (envp[i])
	{
		printf("%d - %s\n", i, envp[i]);
		i++;
	}
}
