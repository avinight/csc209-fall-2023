#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    // Declare any variables you need
    int fd[argc - 1][2];

    
    // Write the code to loop over the command line arguments
    for (int i = 1; i < argc; i++) {
        // Call pipe before we fork
        if (pipe(fd) == -1) {
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
            if (close(fd[0]) == -1) {
                perror("close");
                exit(1);
            }

            // Before we forked, parent had open the reading ends to
            // all previously forked children; so close those.
			for (int j = 1; j < i; j++) {
                if (close(fd[j][0]) == -1) {
                    perror("close");
                    exit(1);
                }
            }

            // Now do the work - write the value in binary to the pipe
			int length = strlen(argv[i]);
            if (write(fd[1], &length, sizeof(int)) != sizeof(int)) {
                perror("write");
                exit(1);
            }

            // Close the pipe since we are done with it.
            if (close(fd[i][1]) == -1) {
                perror("close");
                exit(1);
            }
            exit(0);

        } else {
            // In the parent, but before doing the next loop iteration,
            // close the end of the pipe that we don't want open
            if (close(fd[1]) == -1) {
                perror("close");
                exit(1);
            }
        }
    }
    
    // Only the parent gets here
    int sum = 0;
   
    // Read one integer from each child
    for (int i = 1; i < argc; i++) {
        int length;
        if (read(fd[i][0], &length, sizeof(int)) < 0) {
            perror("read");
            exit(1);
        }
        sum += length;
    }

    
    printf("Sum is %d\n", sum);
    return 0;
}

