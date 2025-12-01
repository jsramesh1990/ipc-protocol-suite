#include "../include/ipc_common.h"
#include "../include/shared_data.h"
#include <sys/ipc.h>
#include <sys/msg.h>

void demo_message_queue() {
    print_header("MESSAGE QUEUES");
    
    int msgid;
    Message msg;
    
    // Create message queue
    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process - Sender
        msg.mtype = 1;
        strcpy(msg.mtext, "Hello from message queue!");
        msg.sender = getpid();
        
        if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        
        printf("Child sent message\n");
        exit(0);
    }
    else if (pid > 0) { // Parent process - Receiver
        wait(NULL);
        
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        
        printf("Parent received message:\n");
        printf("  Type: %ld\n", msg.mtype);
        printf("  Text: %s\n", msg.mtext);
        printf("  Sender PID: %d\n", msg.sender);
        
        // Remove message queue
        msgctl(msgid, IPC_RMID, NULL);
    }
    
    print_footer("MESSAGE QUEUES");
}
