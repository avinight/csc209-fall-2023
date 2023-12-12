#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv) {
    // Declare any variables you need


    // Write the code to loop over the command line arguments.
    // (Remember to skip the executable name.)
    for (int i = 1; i < argc; i++) {
        // call fork
        int result = fork();

        if (result == -1) {   // system call error
            // handle the error
            perror("fork");


        } else if () {  // child process
            // child does their work here


        }
    }

    // Finish the code to sum up the return values from the children



    printf("The length of all the args is %d\n",sum);
    return 0;
}
