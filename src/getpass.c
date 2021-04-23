/**
 * @file getpass.c
 * @author Mikel Aristu, David Cuenca
 *
 * @brief The command used to decrypt the pass in order to access the emerald city.
 *
 * @version 0.2
 * @date 2021-04-14
 *
 * @copyright Copyright (c) 2021
 */

#include "headers/getpass.h"

void docommand()
{
    int pipefd[2];

    if (pipe(pipefd))
    {
        // Get a pipe (buffer and fd pair) from the OS.
        perror("pipe");
        exit(127);
    }

    /** 
     * We are the child process, but since we have TWO commands to execute we
     * need to have two disposable processes, so fork again. 
     */
    switch (fork())
    {
    case -1:
        // In case of error...
        perror("fork");
        exit(127);

    case 0:
        // Child process

        /**
         * Do redirections and close the wrong side of the pipe the other side 
         * of the pipe 
         */
        close(pipefd[0]);

        // dup2() makes newfd be the copy of oldfd, closing newfd first if necessary.

        // Automatically closes previous fd 1
        dup2(pipefd[1], 1);
        // Cleanup
        close(pipefd[1]);

        // exec ls
        execlp("/bin/ls", "ls", (char *)NULL);

        /** 
         * Return value from execlp() can be ignored because if execlp returns at all, the 
         * return value must have been -1, meaning error; and the reason for the error is 
         * stashed in ERRNO.
         */
        perror("/bin/ls");
        exit(127);

    default:
        // Parent process

        /**
         * It is important that the last command in the pipeline is execd by the parent, 
         * because that is the process we want the shell to wait on. That is, the shell 
         * should not loop and print the next prompt, etc, until the LAST process in the 
         * pipeline terminates. 
         * 
         * Normally this will mean that the other ones have terminated as well, because 
         * otherwise their sides of the pipes won't be closed so the later-on processes 
         * will be waiting for more input still.
         */

        // Do redirections and close the wrong side of the pipe

        // The other side of the pipe.
        close(pipefd[1]);
        // Automatically closes previous fd 0.
        dup2(pipefd[0], 0);
        // Cleanup.
        close(pipefd[0]);

        // Execute tr changing the letter b by s
        execlp("/bin/tr", "tr", "b", "s", (char *)NULL);
        perror("/bin/tr");
        exit(127);
    }

    /*
     * When the execlp processes exit, all of their file descriptors are closed.
     * Thus the side of ls command of the pipe will be closed, and thus the "tr" 
     * command will get eof on stdin.  But if we didn't have the close(pipefd[1]) 
     * for 'tr' (in the default: case), the incoming side of the pipe would NOT 
     * be closed (fully), the "tr" command would still have it open, and so tr 
     * itself would not get eof! Try it!
     */
}

int main()
{
    int current_pid, status;
    extern void docommand();

    printf("Decrypting the password...\n");
    /**
     * Important, otherwise the stdout buffer would be present in both processes after the fork()!
     * It could be printed twice...  Or never printed, because of the execlp overwriting this whole 
     * process.
     * 
     * It depends on how it's being buffered.  When doing a fork or execlp, we are careful to empty 
     * our stdio buffers first.
     */
    fflush(stdout);

    switch ((current_pid = fork()))
    {
    case -1:
        perror("fork");
        break;

    case 0:
        /* child */
        docommand();
        break;

    default:
        // Parent; fork() return value is child pid.

        /**
         * Forked will be the one which satisfies the wait(). This mightn't be the case in a more 
         * complex situation, e.g. a shell which has started several "background" processes. 
         */
        printf("fork() returns child pid of %d\n", current_pid);
        wait(&status);
        printf("wait() returns child pid of %d\n", current_pid);

        /**
         * Status, i.e. return value from main() or the value passed to exit(). 
         */
        printf("Child exit status was %d\n", WEXITSTATUS(status));
    }

    return (0);
}
