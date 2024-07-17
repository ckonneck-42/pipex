/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:09:21 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/17 16:40:16 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**create_args(char *arg, char **args)
{
	args = malloc(4 * sizeof(char *));
	if (args == NULL)
	{
		ft_printf("failed to allocate memory for args");
		return (NULL);
	}
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = arg;
	args[3] = NULL;
	return (args);
}

void	child1(char *argv1, char *argv2, int *fd, char **args)
{
	int	infile;

	infile = open(argv1, O_RDONLY);
	if (infile < 0)
	{
		printf("check infile\n");
		//ft_printf("zsh: %s: %s\n", strerror(errno), argv1);
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	args = create_args(argv2, args);
	if (args == NULL)
		exit(EXIT_FAILURE);
	if (execve("/bin/sh", args, NULL) == -1)
	{
		if (errno == ENOENT)
		{
			//perror("execve");
			printf("check child1\n");
			// ft_printf("zsh: %s: %s\n", strerror(errno), argv2);
		}
		else
			perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	child2(char *argv3, char *argv4, int *fd, char **args)
{
	int	outfile;

	outfile = open(argv4, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		printf("check outfile\n");
		//ft_printf("zsh: %s: %s\n", strerror(errno), argv4);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	args = create_args(argv3, args);
	if (args == NULL)
		exit(EXIT_FAILURE);
	if (execve(args[0], args, NULL) == -1)
	{
		if (errno == ENOENT)
		{
			printf("check1\n");
			//ft_printf("zsh: %s: %s\n", strerror(errno), argv3);
		}
		else
			perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent(int *fd, int pid1, int pid2, char **args)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(args);
}

int	main(int argc, char **argv)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**args;

	args = NULL;
	if (argc == 5)
	{
		if (check_pipe(fd) || check_fork(&pid1))
			return (1);
		if (pid1 == 0)
			child1(argv[1], argv[2], fd, args);
		else
		{
			check_fork(&pid2);
			if (pid2 == 0)
				child2(argv[3], argv[4], fd, args);
			else
				parent(fd, pid1, pid2, args);
		}
		return (0);
	}
	else
		ft_printf("not enough or too many arguments");
}
