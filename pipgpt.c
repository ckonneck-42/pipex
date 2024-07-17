#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd[2];
    int pid1;
    int pid2;

    if (argc == 5)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return (1);
        }
        pid1 = fork();
        if (pid1 < 0)
        {
            perror("fork");
            return (2);
        }
        if (pid1 == 0)
        {   // first child
            int infile = open(argv[1], O_RDONLY); //diff
            if (infile < 0)                         //diff
            {
                perror("open infile");              //diff
                return (4);                         //diff
            }
            dup2(infile, STDIN_FILENO);             //diff
            dup2(fd[1], STDOUT_FILENO);             //same
            close(infile);                          //diff
            close(fd[0]);                           //same
            close(fd[1]);                           //same
            char *args[] = {"/bin/sh", "-c", argv[2], NULL};    //same
            execve("/bin/sh", args, NULL);      //same
            perror("execve");                   //new
            exit(EXIT_FAILURE);                 //new
        }
        else                                    //same
        {
            pid2 = fork();                    //  //not wwaiting
            if (pid2 < 0)                          //same
            {
                perror("fork");
                return (3);                     //same more or less
            }
            if (pid2 == 0)
            {   // second child
                int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); //slightly diff
                if (outfile < 0)                //same
                {
                    perror("open outfile");     //not closing fd0
                    return (5);
                }
                dup2(fd[0], STDIN_FILENO);      //same
                dup2(outfile, STDOUT_FILENO);   //same
                close(outfile);                 //same
                close(fd[0]);                   //same
                close(fd[1]);                   //same
                char *args[] = {"/bin/sh", "-c", argv[3], NULL};        //same
                execve("/bin/sh", args, NULL);          //same
                perror("execve");               //similar
                exit(EXIT_FAILURE);             //new
            }   
            else
            {
                close(fd[0]);                   //close here
                close(fd[1]);                   //same
                waitpid(pid1, NULL, 0);         //waiting both here
                waitpid(pid2, NULL, 0);         //waiting both here
            }
        }
        return 0;
    }
    else
    {
        fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
        return 1;
    }
}

// shit works, figure out why