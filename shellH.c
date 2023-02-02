#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80  /* The maximum length command */

int main(int argc, char *argv[])
{
    // char *args[MAX_LINE/2 + 1];  /* command line arguments */
    int should_run = 1;  /* flag to determine when to exit program */
    int pid;
    int exec_status;
    
    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        pid = fork();

        if (pid < 0)
        {
            /* error when forking */
            printf("Error in fork.\n");
        }
        if (pid == 0)
        {
            /* child process */
            printf("Child Process: %s then args %s\n", argv[1], argv[1]);
            // argv[1] is the command, and &argv[1] is the address of rest
            //printf("%s then args %s\n", argv[1], &argv[1]);
            exec_status = execvp(argv[1], &argv[1]); 
        }
        else if (pid > 0)
        {
            /* parent process */
            printf("Parent process: \n");
        }


        break;
    }


    return 0;
}