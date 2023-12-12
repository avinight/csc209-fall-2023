#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];

  /* The user will type in a user name on one line followed by a password 
     on the next.
     DO NOT add any prompts.  The only output of this program will be one 
	 of the messages defined above.
     Please read the comments in validate carefully
   */

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  
  // TODO
  // 1. Create a pipe 
  int fd[2];
  if(pipe(fd) == -1) {
      perror("pipe");
      exit(1);
  }
  // 2. Fork a child process
  pid_t pid = fork();
  if(pid < 0) {
      perror("fork");
      exit(1);
  } 
  // 3. In the child, close the appropriate fd's and call execl to launch
  //    validate, with the read end of the pipe as stdin 
  else if(pid == 0) {
      // child
      if(close(fd[1]) == -1) {
          perror("close");
          exit(1);
      }
      if(dup2(fd[0], STDIN_FILENO) == -1) {
          perror("dup2");
          exit(1);
      }
      if(close(fd[0]) == -1) {
          perror("close");
          exit(1);
      }
      if(execl("./validate", "validate", NULL) == -1) {
          perror("execl");
          exit(1);
      }
  } 
  // 4. In the parent, write the contents of user_id to the pipe, close the
  //    appropriate fd's and read from the pipe the response from validate
  else {
      // parent
      if(close(fd[0]) == -1) {
          perror("close");
          exit(1);
      }
      if(write(fd[1], user_id, MAX_PASSWORD) == -1) {
          perror("write");
          exit(1);
      }
      if(write(fd[1], password, MAX_PASSWORD) == -1) {
          perror("write");
          exit(1);
      }
      if(close(fd[1]) == -1) {
          perror("close");
          exit(1);
      }
      // 5. Wait for the child to finish
      int status;
      if(wait(&status) == -1) {
          perror("wait");
          exit(1);
      }
  // 6. Based on the value returned by the child, print the appropriate
  //    message:
  //    INVALID if the user id exists, but the password does not match.
  //    SUCCESS if the user id and password match.
  //    NO_USER if the user id is not recognized
      if(WIFEXITED(status)) {
          int exit_status = WEXITSTATUS(status);
          if(exit_status == 0) {
              printf(SUCCESS);
          } else if(exit_status == 2) {
              printf(INVALID);
          } else if(exit_status == 3) {
              printf(NO_USER);
          } else {
              fprintf(stderr, "Error: invalid exit status from validate\n");
              exit(1);
          }
      } else {
          fprintf(stderr, "Error: validate did not exit normally\n");
          exit(1);
      }
  }
  return 0;
}
