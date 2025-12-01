#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#define BUFFER_SIZE 10
#define SHM_KEY 0x1234
#define SEM_KEY 0x5678

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedBuffer;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait(int semid, int semnum) {
    struct sembuf op = {semnum, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid, int semnum) {
    struct sembuf op = {semnum, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    // Create shared memory
    int shmid = shmget(SHM_KEY, sizeof(SharedBuffer), IPC_CREAT | 0666);
    SharedBuffer *buffer = shmat(shmid, NULL, 0);
    
    // Initialize shared buffer
    buffer->in = 0;
    buffer->out = 0;
    
    // Create semaphores
    int semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    
    // Initialize semaphores
    union semun arg;
    arg.val = BUFFER_SIZE;  // Empty slots
    semctl(semid, 0, SETVAL, arg);
    arg.val = 0;            // Filled slots
    semctl(semid, 1, SETVAL, arg);
    
    if (fork() == 0) {
        // Producer
        for (int i = 1; i <= 20; i++) {
            sem_wait(semid, 0);  // Wait for empty slot
            
            buffer->buffer[buffer->in] = i;
            printf("Producer produced: %d\n", i);
            buffer->in = (buffer->in + 1) % BUFFER_SIZE;
            
            sem_signal(semid, 1);  // Signal filled slot
            usleep(100000);  // 100ms
        }
        exit(0);
    }
    
    if (fork() == 0) {
        // Consumer
        for (int i = 1; i <= 20; i++) {
            sem_wait(semid, 1);  // Wait for filled slot
            
            int item = buffer->buffer[buffer->out];
            printf("Consumer consumed: %d\n", item);
            buffer->out = (buffer->out + 1) % BUFFER_SIZE;
            
            sem_signal(semid, 0);  // Signal empty slot
            usleep(150000);  // 150ms
        }
        exit(0);
    }
    
    wait(NULL);
    wait(NULL);
    
    // Cleanup
    shmdt(buffer);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    
    return 0;
}
