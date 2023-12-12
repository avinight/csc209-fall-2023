#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "bitmap.h"


#define ERROR_MESSAGE "Warning: one or more filter had an error, so the output image may not be correct.\n"
#define SUCCESS_MESSAGE "Image transformed successfully!\n"


/*
 * Check whether the given command is a valid image filter, and if so,
 * run the process.
 *
 * We've given you this function to illustrate the expected command-line
 * arguments for image_filter. No further error-checking is required for
 * the child processes.
 */
void run_command(const char *cmd) {
    if (strcmp(cmd, "copy") == 0 || strcmp(cmd, "./copy") == 0 ||
        strcmp(cmd, "greyscale") == 0 || strcmp(cmd, "./greyscale") == 0 ||
        strcmp(cmd, "gaussian_blur") == 0 || strcmp(cmd, "./gaussian_blur") == 0 ||
        strcmp(cmd, "edge_detection") == 0 || strcmp(cmd, "./edge_detection") == 0) {
        execl(cmd, cmd, NULL);
    } else if (strncmp(cmd, "scale", 5) == 0) {
        // Note: the numeric argument starts at cmd[6]
        execl("scale", "scale", cmd + 6, NULL);
    } else if (strncmp(cmd, "./scale", 7) == 0) {
        // Note: the numeric argument starts at cmd[8]
        execl("./scale", "./scale", cmd + 8, NULL);
    } else {
        fprintf(stderr, "Invalid command '%s'\n", cmd);
        exit(1);
    }
}


// TODO: Complete this function.
/*
 * 1. Create one new process for each filter specified by the command-line arguments.
 *
 * 2. Connect the processes properly to each other (and to the input and output files) using pipes. Remember that each filter process can only communicate using its stdin/stdout, meaning that dup2 must be used to redirect each of their stdins and stdouts.
 *
 * 3. The filters must process the image in the same order the command-line arguments are specified by the user.
 * Wait for all processes to complete, and print a success message to the user. 
 * If one or more of the processes failed (exit with non-zero status), print a warning message to the user. 
 * We’ve provided string constants for these messages for you in the starter code.
*/
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: image_filter input output [filter ...]\n");
        exit(1);
    }
    
    int processes = argc - 3;
    int fd[argc - 3][2];
    int pid;

    // Create (argc - 3) pipes
    for (int i = 0; i < processes; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Open input file
    int fp = open(argv[1], O_RDONLY);
    if (fp == -1) {
        perror("fopen");
        exit(1);
    }
    
    // Open output file
    int fp2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (fp2 == -1) {
        perror("fopen");
        exit(1);
    }
    
    // Redirect STDIN of original parent process to input file
    if (dup2(fp, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    if (close(fp)) {
        perror("close");
        exit(1);
    }

    // Special Case: No filters
    if (argc == 3) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            if (dup2(fp2, STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(1);
            }
            if (close(fp2)) {
                perror("close");
                exit(1);
            }
            if (execl("./copy", "./copy", NULL) == -1) {
                perror("execl");
                exit(1);
            }
        }
    }
    
    // Fork child processes
    for (int i = 3; i < argc; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        // Child
        if (pid == 0) {
            // The first program will read from STDIN
            if (i > 3) {
                if ((fd[i - 4][0] != STDIN_FILENO) && (dup2(fd[i - 4][0], STDIN_FILENO) == -1)) {
                    perror("dup2");
                    exit(1);
                }
            }
            // The last program will write to STDOUT
            if (i < argc - 1) {
                if ((fd[i - 3][1] != STDOUT_FILENO) && (dup2(fd[i - 3][1], STDOUT_FILENO) == -1)) {
                    perror("dup2");
                    exit(1);
                }
            }
            if (i == argc - 1) {
                // Redirect STDOUT of last child process to output file
                if (dup2(fp2, STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(1);
                }
                if (close(fp2)) {
                    perror("close");
                    exit(1);
                }
            }
            // Close all pipes in child process
            for (int i = 0; i < processes; i++) {
                if (close(fd[i][0]) == -1){
                    perror("close");
                    exit(1);
                }
                if (close(fd[i][1]) == -1){
                    perror("close");
                    exit(1);
                }
            }
            // Run command of child process
            run_command(argv[i]);
        } 
    }
    
    // Parent
    // Close all pipes in parent process
    for (int i = 0; i < processes; i++) {
         if (close(fd[i][0]) == -1){
            perror("close");
            exit(1);
         }
         if (close(fd[i][1]) == -1){
            perror("close");
            exit(1);
         }
    }

    // Wait for child processes to complete
    int stat;
    for (int i = 2; i < argc; i++) {
        if (wait(&stat) == -1) {
            perror("wait");
            exit(1);
        }
        if (WIFEXITED(stat)) {
            if (WEXITSTATUS(stat) != 0) {
                fprintf(stderr, ERROR_MESSAGE);
                exit(1);
            }
            if (WEXITSTATUS(stat) == 0) {
                printf(SUCCESS_MESSAGE);
                exit(0);
            }
        }
    }
    return 0;
}
