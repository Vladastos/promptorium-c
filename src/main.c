#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

  // get the current working directory
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("Current working dir: %s\n", cwd);

  // get the user name
  char *user = getlogin();
  printf("User name: %s\n", user);
  printf("Hello, World!\n");
  return 0;
}