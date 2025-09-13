#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// #include "kernel/proc.h" // For pstat struct



void work(int id, int iterations) {
    for(volatile int i = 0; i < iterations; i++) {
        if(i % 1000000 == 0) {
            fprintf(1, "Process %d: iteration %d\n", id, i/1000000);
        }
    }
    fprintf(1, "Process %d completed\n", id);
}

int main() {
    fprintf(1, "=== FCFS Test ===\n");
    
    // Create processes
    for(int i = 0; i < 3; i++) {
        if(fork() == 0) {
            fprintf(1, "Process %d started\n", getpid());
            work(getpid(), 20000000);
            exit(0);
        }
    }
    
    work(getpid(), 30000000);
    
    for(int i = 0; i < 3; i++) wait(0);
    fprintf(1, "FCFS test completed\n");
    exit(0);
}