#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    // Declare any variables you need
    int fd[argc - 1][2];
    int result;
    int value;
    char buffer[100];
    int num_read;
    int status;
    int i;
    
    // Write the code to loop over the command line arguments
    for (int i = 1; i < argc; i++) {
        // Call pipe before we fork
        result = pipe(fd);
        if (result < 0) {
            perror("pipe");
            exit(1);
        }

        // Call fork
        int result = fork();
		if (result < 0) {
			perror("fork");
			exit(1);

		} else if (result == 0) {
            // Child only writes to the pipe, so close reading end
            close(fd[0]);

            // Before we forked, parent had open the reading ends to
            // all previously forked children; so close those.
            for (int j = 0; j < i; j++) {
                close(fd[j][0]);
            }

            // Now do the work - write the value in binary to the pipe
			int length = strlen(argv[i]);
            write(fd[i][1], &length, sizeof(int));


            // Close the pipe since we are done with it.
            close(fd[i][1]);

            exit(0);

        } else {
            // In the parent, but before doing the next loop iteration,
            // close the end of the pipe that we don't want open
            close(fd[i][1]);

        }
    }
    
    // Only the parent gets here
    int sum = 0;
   
    // Read one integer from each child
    for (int i = 1; i < argc; i++) {
        num_read = read(fd[i][0], &value, sizeof(int));
        if (num_read < 0) {
            perror("read");
            exit(1);
        }
        sum += value;
    }
    
    printf("Sum is %d\n", sum);
    return 0;
}

