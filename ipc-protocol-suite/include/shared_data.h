#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#define SHM_SIZE 1024

typedef struct {
    int counter;
    char message[MAX_MSG_SIZE];
    pid_t sender_pid;
    time_t timestamp;
} SharedData;

// Message structure for message queues
typedef struct {
    long mtype;
    char mtext[MAX_MSG_SIZE];
    pid_t sender;
} Message;

#endif // SHARED_DATA_H
