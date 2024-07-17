#include "pipex.h"

int main(int argc, char **argv)
{
	
	int fd[2];
	int pid1;
	int pid2;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return(1);
		pid1 = fork();
		if (pid1 < 0)
			return (2);
		if (pid1 == 0)
		{	// child
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			char *args[] = {"/bin/sh", "-c", argv[2], NULL};
    		execve("/bin/sh", args, NULL);
		}
		else
		{
			close(fd[1]);
			waitpid(pid1, NULL, 0);
			pid2 = fork();
			if (pid2 < 0)
				return (3);
			if (pid2 == 0)
			{ // second child
				int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, NULL);
				if (outfile < 0)
    	        {
					close(fd[0]);
    	            perror("open");
    	            return (4);
    	        }
				dup2(fd[0], STDIN_FILENO);
				dup2(outfile, STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(outfile);
				char *args[] = {"/bin/sh", "-c", argv[3], NULL};
    			execve("/bin/sh", args, NULL);
			}
			else
			{
				close(fd[0]);
				waitpid(pid2, NULL, 0);
			}
		}
    	return 0;
	}
	else
		ft_printf("wperoitfgjw");
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:09:21 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/17 10:34:42 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"




char **create_args(char *arg)
{
	char **args = malloc(4 * sizeof(char *));
	if (args == NULL)
	{
		perror("failed to allocate memory for args");
		return (NULL);
	}
	args[0] = "/bin/sh";
    args[1] = "-c";
    args[2] = arg;
    args[3] = NULL;
	return (args);
}







int main(int argc, char **argv)
{
	int fd[2];
	int pid1;
	int pid2;
	int infile;
	int outfile;
	char **args = NULL;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return(1);
		pid1 = fork();
		if (pid1 < 0)
			return (2);
		if (pid1 == 0)
		{	// child
			infile = open(argv[1], O_RDONLY);
			if (infile < 0)
				perror("open infile");
			dup2(infile, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(infile);
			close(fd[0]);
			close(fd[1]);
			if ((args = create_args(argv[2])) == NULL)
				exit(EXIT_FAILURE);
    		execve("/bin/sh", args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			pid2 = fork();
			if (pid2 < 0)
				return (3);
			if (pid2 == 0)
			{ // second child
				outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (outfile < 0)
    	        {
    	            perror("open outfile");
    	            return (4);
    	        }
				dup2(fd[0], STDIN_FILENO);
				dup2(outfile, STDOUT_FILENO);
				close(outfile);
				close(fd[0]);
				close(fd[1]);
				if ((args = create_args(argv[3])) == NULL)
					exit(EXIT_FAILURE);
    			execve("/bin/sh", args, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				close(fd[0]);
				close(fd[1]);
				waitpid(pid1, NULL, 0);
				waitpid(pid2, NULL, 0);
				free(args);
			}
		}
    	return 0;
	}
	else
	{
		ft_printf("not enough or too many arguments");
		return (1);
	}
		
}








////////////////////////////////////////////////////////

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:09:21 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/17 11:07:55 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"




char **create_args(char *arg)
{
	char **args = malloc(4 * sizeof(char *));
	if (args == NULL)
	{
		perror("failed to allocate memory for args");
		return (NULL);
	}
	args[0] = "/bin/sh";
    args[1] = "-c";
    args[2] = arg;
    args[3] = NULL;
	return (args);
}


void child1(char *argv2, char **args, int infile, int *fd)
{
	if (infile < 0)
	perror("open infile");
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	if ((args = create_args(argv2)) == NULL)
		exit(EXIT_FAILURE);
  	execve("/bin/sh", args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}	

void child2(char *argv3, int outfile, int *fd, char **args)
{
	if (outfile < 0)  
    	perror("open outfile");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	if ((args = create_args(argv3)) == NULL)
		exit(EXIT_FAILURE);
	execve("/bin/sh", args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}




int main(int argc, char **argv)
{
	int fd[2];
	int pid1;
	int pid2;
	int infile;
	int outfile;
	char **args = NULL;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return(1);
		pid1 = fork();
		if (pid1 < 0)
			return (2);
		if (pid1 == 0)
		{	// child
			infile = open(argv[1], O_RDONLY);
			child1(argv[2], args, infile, fd);
		}
		else
		{
			pid2 = fork();
			if (pid2 < 0)
				return (3);
			if (pid2 == 0)
			{ // second child
				outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				child2(argv[3], outfile, fd, args);
			}
			else
			{
				close(fd[0]);
				close(fd[1]);
				waitpid(pid1, NULL, 0);
				waitpid(pid2, NULL, 0);
				free(args);
			}
		}
    	return 0;
	}
	else
	{
		ft_printf("not enough or too many arguments");
		return (1);
	}
		
}

////////////////////////////////////////////////////