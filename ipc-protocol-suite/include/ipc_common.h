#ifndef IPC_COMMON_H
#define IPC_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

// Common definitions
#define MAX_MSG_SIZE 256
#define FIFO_NAME "/tmp/ipc_fifo"
#define SHM_KEY 1234
#define MSG_KEY 5678
#define SEM_KEY 9999

// Function prototypes
void print_header(const char *protocol);
void print_footer(const char *protocol);
void delay_ms(int milliseconds);

// Utility functions
char* get_timestamp();

#endif // IPC_COMMON_H
