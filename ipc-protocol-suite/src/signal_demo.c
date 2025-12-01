#include "../include/ipc_common.h"
#include <signal.h>

volatile sig_atomic_t signal_received = 0;

void signal_handler(int sig) {
    signal_received = 1;
    printf("Signal %d received!\n", sig);
}

void demo_signals() {
    print_header("SIGNALS");
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process
        // Install signal handler
        signal(SIGUSR1, signal_handler);
        
        printf("Child waiting for signal...\n");
        
        // Wait for signal
        while (!signal_received) {
            pause();
        }
        
        printf("Child received signal, exiting...\n");
        exit(0);
    }
    else if (pid > 0) { // Parent process
        sleep(1); // Give child time to set up handler
        
        printf("Parent sending SIGUSR1 to child (PID: %d)\n", pid);
        
        // Send signal to child
        kill(pid, SIGUSR1);
        
        wait(NULL);
    }
    
    print_footer("SIGNALS");
}
