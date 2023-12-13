#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char name[100]; // Global variable to store the name

void sing(int signum) {
    printf("Happy Birthday to you,\n");
    printf("Happy Birthday to you,\n");
    sleep(10);
    printf("Happy Birthday dear %s,\n", name);
    printf("Happy Birthday to you.\n");
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    strncpy(name, argv[1], sizeof(name) - 1); // Copy the name into the global variable

    struct sigaction sa;
    sa.sa_handler = sing;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaddset(&sa.sa_mask, SIGINT); // Block SIGINT during execution of sing

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    while(1) {
        // Infinite loop
    }

    return 0;
}