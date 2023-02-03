#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 80

typedef struct
{
    char *inputBuffer;
    char *Arguments[3];
} Command;

Command **addToHistory(Command **args, Command *arg)
{
    for (int i = 0; i < 4; i++)
    {
        args[i] = args[i + 1];
    }
    args[4] = arg;
    return args;
}

int main(void)
{
    int should_run = 1;

    Command **history = malloc(sizeof(Command) * 5);
    for (int i = 0; i < 5; i++)
    {
        Command *command;
        history[i] = command;
    }
    int historySize = 0;

    while (should_run)
    {
        printf(">osh ");
        fflush(stdout);

        char *inputBuffer; // https://c-for-dummies.com/blog/?p=1112
        size_t bufsize = (MAX_LINE / 2 + 1);
        size_t inputLen;

        Command *arg = malloc(sizeof(Command));
        arg->inputBuffer = (char *)malloc(bufsize * sizeof(char));

        inputLen = getline(&arg->inputBuffer, &bufsize, stdin);

        // Split input buffer into program name, and arguments
        char *programName = strtok(arg->inputBuffer, " \t\r\n\f\v");
        char *programArguments = strtok(NULL, "\n");

        arg->Arguments[0] = programName;
        arg->Arguments[1] = programArguments;
        arg->Arguments[2] = NULL;
 
        int execStatus = 0;

        pid_t pid = fork();
        if (pid < 0)
        {
            /* error when forking */
            printf("Error in fork.\n");
        }
        else if (pid == 0)
        {
            /* child process */
            //printf("Child Process: \n");
            // argv[1] is the command, and &argv[1] is the address of rests
            if (!strcmp(arg->Arguments[0], "!!"))
            {
                if (historySize != 0) {
                    arg = history[4];
                    execStatus = execvp(arg->Arguments[0], &arg->Arguments);
                } else {
                    printf("No commands in history\n");
                    execStatus = -1;
                    return 0;
                }

            }
            else if (!strcmp(arg->Arguments[0], "history"))
            {
                for (int i = 4; i>=5-historySize; --i){
                    if (history[i]->Arguments[0] != NULL) {
                        if (history[i]->Arguments[1] != NULL) {
                            printf("%s %s\n", history[i]->Arguments[0], history[i]->Arguments[1]);
                        } else {
                            printf("%s\n", history[i]->Arguments[0]);
                        }
                    }
                }
            }
            else
            {
                execStatus = execvp(arg->Arguments[0], &arg->Arguments);
            }
        }
        else if (pid > 0)
        {
            /* parent process */
            wait(NULL);
            if (execStatus == 0)
            {
                // printf("ExecStatus: %d, for arg: %s\n", execStatus, arg);
                char *actualCommand = arg->Arguments[0];
                if (!strcmp(arg->Arguments[0], "!!")){
                    arg = history[4];
                }
                if (strcmp(arg->Arguments[0], "history")){
                    if (!(!strcmp(actualCommand, "!!") && historySize == 0)){
                        history = addToHistory(history, arg);
                        if (historySize < 5)
                            historySize++;
                    }
                }

            } else {
                printf("Error executing last command\n");
            }
            // printf("Child Process with pid: %d Finished Executing.\n", pid);
        }
    }

    return 0;
}
