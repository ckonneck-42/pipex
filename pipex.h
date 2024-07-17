/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:32:36 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/17 16:18:57 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

int	check_fork(int *pid);
int	check_pipe(int *fd);
#endif