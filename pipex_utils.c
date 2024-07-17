/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:12:01 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/17 16:14:57 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (1);
	return (0);
}

int	check_fork(int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return (1);
	return (0);
}