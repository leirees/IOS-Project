/**
 * @file getpass.c
 * @author Mikel Aristu
 *
 * @brief The command used to decrypt the pass in order to access the emerald city.
 *
 * @version 0.1
 * @date 2021-04-14
 *
 * @copyright Copyright (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid, status;
    extern void docommand();

    printf("Decrypting the password...\n");
    fflush(stdout);  /* important, otherwise the stdout buffer would be
                      * present in both processes after the fork()!
                      * It could be printed twice...  Or never printed,
                      * because of the execlp overwriting this whole process.
                      * It depends on how it's being buffered.  When doing
                      * a fork or execlp, we are careful to empty our stdio
                      * buffers first.  */

    switch ((pid = fork())) {
        case -1:
        perror("fork");
        break;
    case 0:
        /* child */
        docommand();
        break;  
    default:
        /* parent; fork() return value is child pid */
        /* These two pids output below will be the same: the process we
         * forked will be the one which satisfies the wait().  This mightn't
         * be the case in a more complex situation, e.g. a shell which has
         * started several "background" processes. */
        printf("fork() returns child pid of %d\n", pid);
        pid = wait(&status);
        printf("wait() returns child pid of %d\n", pid);
        printf("Child exit status was %d\n", WEXITSTATUS(status));
                /* status is a two-byte value; the upper byte is the exit
                 * status, i.e. return value from main() or the value passed
                 * to exit(). */
    }
    return(0);
}

void docommand() {
    int pipefd[2];

    /* get a pipe (buffer and fd pair) from the OS */
    if (pipe(pipefd)) {
        perror("pipe");
        exit(127);
    }

    /* We are the child process, but since we have TWO commands to execute we
     * need to have two disposable processes, so fork again */
    switch (fork()) {
    case -1:
        /*in case of error*/
        perror("fork");
        exit(127);
    case 0:
        /* child */
        /* do redirections and close the wrong side of the pipe */
        close(pipefd[0]);  /* the other side of the pipe */
        /*dup2() makes newfd be the copy of oldfd, closing newfd first if necessary*/
        dup2(pipefd[1], 1);  /* automatically closes previous fd 1 */
        close(pipefd[1]);  /* cleanup */
        /* exec ls */
        execlp("/bin/ls", "ls", (char *)NULL);
        /* return value from execlp() can be ignored because if execlp returns
         * at all, the return value must have been -1, meaning error; and the
         * reason for the error is stashed in ERRNO */
        perror("/bin/ls");
        exit(127);
    default:
        /* parent */
        /*
         * It is important that the last command in the pipeline is execd
         * by the parent, because that is the process we want the shell to
         * wait on.  That is, the shell should not loop and print the next
         * prompt, etc, until the LAST process in the pipeline terminates.
         * Normally this will mean that the other ones have terminated as
         * well, because otherwise their sides of the pipes won't be closed
         * so the later-on processes will be waiting for more input still.
         */
        /* do redirections and close the wrong side of the pipe */
        close(pipefd[1]);  /* the other side of the pipe */
        dup2(pipefd[0], 0);  /* automatically closes previous fd 0 */
        close(pipefd[0]);  /* cleanup */
        /* execute tr changing the letter b by s*/
        execlp("/bin/tr", "tr", "b", "s", (char *)NULL);
        perror("/bin/tr");
        exit(127);
    }

    /*
     * When the execlp processes exit, all of their file descriptors are closed.
     * Thus the side of ls command of the pipe will be closed, and thus the
     * "tr" command will get eof on stdin.  But if we didn't have the
     * close(pipefd[1]) for 'tr' (in the default: case), the incoming side
     * of the pipe would NOT be closed (fully), the "tr" command would still
     * have it open, and so tr itself would not get eof!  Try it!
     */
}
