#include "../include/ipc_common.h"

void demo_fifos() {
    print_header("FIFOS (Named Pipes)");
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process - Writer
        // Create FIFO
        mkfifo(FIFO_NAME, 0666);
        
        int fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        
        char msg[] = "Hello from FIFO!";
        printf("Child writing to FIFO: %s\n", msg);
        write(fd, msg, strlen(msg) + 1);
        
        close(fd);
        exit(0);
    }
    else if (pid > 0) { // Parent process - Reader
        sleep(1); // Give child time to create FIFO
        
        int fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        
        char buffer[MAX_MSG_SIZE];
        read(fd, buffer, sizeof(buffer));
        printf("Parent read from FIFO: %s\n", buffer);
        
        close(fd);
        unlink(FIFO_NAME); // Remove FIFO
        wait(NULL);
    }
    
    print_footer("FIFOS");
}
