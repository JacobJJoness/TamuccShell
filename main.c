#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

//-----Intro function-----//
// This function grabs user
// input and returns it.
// Also prints the shell name

char *intro()
{
    printf("TamuccShell>> ");
    char *userInput = NULL;
    static char dataStr[200];
    int i = 0;

    if (fgets(dataStr, 200, stdin) == NULL) // The statement reads a line
    {
        printf("Error\n");
        return userInput;
    }
    userInput = dataStr;

    return userInput;
}

//-----Tokenizer function-----//
// Variables:Char**, Char*,
// toks is to hold arguments
// data holds user input data
// which are the commands

int tokenizer(char **toks, char *data)
{

    int i = 0;

    data[strlen(data) - 1] = '\0'; // It replaces newline ch with null

    char *token = strtok(data, " "); // Returns first token with delimiter space

    // strcpy(command,token);// stores first token in this pointer to seperate our command from our arguements
    // Keep extracting tokens

    int err = 0;

    while (token != NULL)
    {
        // NOTE/FIX: check against limit of toks
        if (i >= (10 - 1))
        {
            printf("too many tokens\n");
            err = 1;
            break;
        }

        // NOTE/BUG: toks is a _pointer_ array
        toks[i] = token;
        token = strtok(NULL, " ");
        i += 1;
    }

    toks[i] = (char *)0;

    return err;
}

int main(void)
{
    char *tokens; // User given tokens fed into tokenizer functions
    // --------VARIABLES FOR EXECV FUNCTION-----------------//
    int pid;      // process ID for child process
    int status;   // status for child process, this will be an indicator for the parent process to continue
    char *folder; // Destination for command to execute
    // reservation for commands argv[0] will be the actual command argv[1] will
    // be arguements ,argv[2] null for termination
    // NOTE/BUG: don't use hardwired "magic" numbers

    char *argv[10];

    folder = (char *)malloc(200); // Allocate 20 character positions

    int i; // iterator used with for loop below.

    // -------VARIABLE for Tokenizer-------//
    char *userInput; // storage space for user input from intro function

    // ----MAIN LOOP----//
    int active = 1; // used for while loop below this line

    while (active)
    {

        // ---FUNCTION CALLS---//
        userInput = intro(); // Calling introduction program that grabs user input and displays the shell prompt
        // fills command and arguement with tokenized values

        // skip command if parsing error
        if (tokenizer(argv, userInput))
            continue;

        if (strcmp(argv[0], "exit") == 0) // check for exit call
        {
            active = 0;
        }

        // else if(strcmp(argv[0],"hist") == 0){ // check for hist call
        // commandPrinter(prevComs);

        // }

        else
        {

            folder = strcpy(folder, "/bin/"); // Destination setup for bin, so we may access commands.

            folder = strcat(folder, argv[0]); // Destination specification of command IE "ls"

            pid = fork(); // creates child process
            if (pid == 0)
            {                        // checks if this process is the child process
                execv(folder, argv); // call to the function in child process; execute command and exit from the child process

                printf("\nCommand Failed\n"); // only runs if execv call has failed.
                exit(0);
            }
            else
            {
                wait(&status); // makes parent process wait for the child process to
            }
        }
    }

    return 0;
}