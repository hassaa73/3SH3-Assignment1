#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80

int main(void)  {
    int should_run = 1;

    while (should_run) {
        printf(">osh ");
        fflush(stdout);

        char *inputBuffer; // https://c-for-dummies.com/blog/?p=1112
        size_t bufsize = (MAX_LINE/2 +1);
        size_t inputLen;

        inputBuffer = (char *)malloc(bufsize * sizeof(char));
        inputLen = getline(&inputBuffer,&bufsize,stdin);

        //Split input buffer into program name, and arguments
        char *programName = strtok(inputBuffer, " ");
        char *programArguments = strtok(NULL, "\0");

        //remove trailing newline characters
        //programName[strcspn(programName, "\n")] = 0; 
        //programArguments[strcspn(programArguments, "\n")] = 0;
        printf("Program Name = %s\n", programName);
        printf("Program Arguments = %s\n", programArguments);

        pid_t pid = fork();
        int execStatus;

        if (pid < 0)
        {
            /* error when forking */
            printf("Error in fork.\n");
        }
        if (pid == 0)
        {
            /* child process */
            printf("Child Process: \n");
            // argv[1] is the command, and &argv[1] is the address of rest
            execStatus = execvp(programName, programArguments); 
            //return execStatus;
            exit(0);
        }
        else if (pid > 0)
        {
            /* parent process */
            wait(NULL);
            printf("Child Process with pid: %d Finished Executing.\n", pid);
        }

    }


    return 0;
}