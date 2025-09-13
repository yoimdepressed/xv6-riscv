#include "kernel/types.h"
#include "user/user.h"

// A simple function to keep the CPU busy
void spin_loop(int id) {
  printf("Process %d started spinning.\n", id);
  while (1) {
    // This infinite loop consumes CPU cycles
  }
}

int main(int argc, char *argv[]) {
  int num_children = 3; // Let's create 3 CPU-hungry children

  printf("Starting CFS test with %d children...\n", num_children);

  for (int i = 0; i < num_children; i++) {
    int pid = fork();
    if (pid == 0) {
      // This is the child process
      spin_loop(getpid());
      exit(0); // This line will never be reached
    }
  }

  // The parent process waits for a moment and then prints procdump instructions
  printf("Parent process is waiting. Press Ctrl+P to see scheduler status.\n");
  
  // The parent can just wait for its children
  for (int i = 0; i < num_children; i++) {
    wait(0);
  }

  exit(0);
}