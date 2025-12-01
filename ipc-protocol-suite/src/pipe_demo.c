#include "../include/ipc_common.h"

void demo_pipes() {
    print_header("PIPES");
    
    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello from pipe!";
    char read_msg[MAX_MSG_SIZE];
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if (pid == 0) { // Child process
        close(pipefd[1]); // Close write end
        
        // Read from pipe
        read(pipefd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        
        close(pipefd[0]);
        exit(0);
    }
    else if (pid > 0) { // Parent process
        close(pipefd[0]); // Close read end
        
        // Write to pipe
        printf("Parent sending: %s\n", write_msg);
        write(pipefd[1], write_msg, strlen(write_msg) + 1);
        
        close(pipefd[1]);
        wait(NULL); // Wait for child
    }
    
    print_footer("PIPES");
}
