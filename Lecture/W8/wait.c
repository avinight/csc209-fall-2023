#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*
 * For this question you will write a program that forks one child for each command line argument. 
 * The child computes the length of the command line argument and exits with that integer as the return value. 
 * The parent sums these return codes and reports the total length of all the command line arguments together. 
 * For example, if your program is called spread_the_work and is called as spread_the_work divide the load it prints
 * The length of all the args is 13. We have provided some parts of the code and you must work within this framework 
 * and complete the missing pieces. You do not need to write include statements.
 */
int main(int argc, char **argv) {
    // Declare any variables you need
    int sum = 0;
    int fd[2];
    int result;

    // Write the code to loop over the command line arguments.
    // (Remember to skip the executable name.)
    for (int i = 1; i < argc; i++) {
        // call fork
        int result = fork();

        if (result == -1) {   // system call error
            // handle the error
            perror("fork");
            exit(1);

        } else if (result == 0) {   // child process
            // child does their work here
            int length = strlen(argv[i]);
            exit(length);


        }
    }

    // Finish the code to sum up the return values from the children
    for (int i = 1; i < argc; i++) {
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            exit(1);
        } else if (WIFEXITED(status)) {
            sum += WEXITSTATUS(status);
        }
    }
    printf("The length of all the args is %d\n",sum);
    return 0;
}
