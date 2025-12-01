#include "../include/ipc_common.h"
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/ipc_socket"

void demo_sockets() {
    print_header("UNIX DOMAIN SOCKETS");
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process - Server
        int server_fd, client_fd;
        struct sockaddr_un server_addr, client_addr;
        socklen_t client_len = sizeof(client_addr);
        char buffer[MAX_MSG_SIZE];
        
        // Create socket
        server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (server_fd == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }
        
        // Configure server address
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, SOCKET_PATH);
        
        // Bind socket
        unlink(SOCKET_PATH); // Remove if exists
        if (bind(server_fd, (struct sockaddr*)&server_addr, 
                sizeof(server_addr)) == -1) {
            perror("bind");
            exit(EXIT_FAILURE);
        }
        
        // Listen for connections
        listen(server_fd, 5);
        
        // Accept connection
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, 
                          &client_len);
        
        // Receive message
        read(client_fd, buffer, sizeof(buffer));
        printf("Server received: %s\n", buffer);
        
        // Send response
        char *response = "Hello from server!";
        write(client_fd, response, strlen(response) + 1);
        
        close(client_fd);
        close(server_fd);
        unlink(SOCKET_PATH);
        exit(0);
    }
    else if (pid > 0) { // Parent process - Client
        sleep(1); // Give server time to start
        
        int sockfd;
        struct sockaddr_un server_addr;
        char buffer[MAX_MSG_SIZE];
        
        // Create socket
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sockfd == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }
        
        // Configure server address
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, SOCKET_PATH);
        
        // Connect to server
        if (connect(sockfd, (struct sockaddr*)&server_addr, 
                   sizeof(server_addr)) == -1) {
            perror("connect");
            exit(EXIT_FAILURE);
        }
        
        // Send message
        char *message = "Hello from client!";
        printf("Client sending: %s\n", message);
        write(sockfd, message, strlen(message) + 1);
        
        // Receive response
        read(sockfd, buffer, sizeof(buffer));
        printf("Client received: %s\n", buffer);
        
        close(sockfd);
        wait(NULL);
    }
    
    print_footer("UNIX DOMAIN SOCKETS");
}
