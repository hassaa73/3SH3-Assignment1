#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
        char *Arguments[3];// = malloc(sizeof(char*)*2);
        inputLen = getline(&inputBuffer,&bufsize,stdin);

        //Split input buffer into program name, and arguments
        char *programName = strtok(inputBuffer, " \t\r\n\f\v");
        char *programArguments = strtok(NULL, "\n");

        Arguments[0] = programName;
        Arguments[1] = programArguments;
        Arguments[2] = NULL;

        //remove trailing newline characters
        //programName[strcspn(programName, "\n")] = 0; 
        //programArguments[strcspn(programArguments, "\n")] = 0;
        //printf("Program Name = %s\n", programName);
        //printf("Program Arguments = %s\n", Arguments[1]);
        //printf("Program Arguments2 = %s\n", Arguments[2]);


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
            execStatus = execvp(Arguments[0], &Arguments); 
            printf("Exec Status Child Process: %d\n", execStatus);
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