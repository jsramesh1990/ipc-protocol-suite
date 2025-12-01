#include "../include/ipc_common.h"
#include "../include/shared_data.h"
#include <sys/ipc.h>
#include <sys/shm.h>

void demo_shared_memory() {
    print_header("SHARED MEMORY");
    
    int shmid;
    SharedData *shared_data;
    
    // Create shared memory segment
    shmid = shmget(SHM_KEY, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    // Attach shared memory
    shared_data = (SharedData *)shmat(shmid, NULL, 0);
    if (shared_data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process
        // Write to shared memory
        shared_data->counter = 42;
        strcpy(shared_data->message, "Hello from shared memory!");
        shared_data->sender_pid = getpid();
        shared_data->timestamp = time(NULL);
        
        printf("Child wrote to shared memory\n");
        
        // Detach shared memory
        shmdt(shared_data);
        exit(0);
    }
    else if (pid > 0) { // Parent process
        wait(NULL); // Wait for child
        
        printf("Parent reading from shared memory:\n");
        printf("  Counter: %d\n", shared_data->counter);
        printf("  Message: %s\n", shared_data->message);
        printf("  Sender PID: %d\n", shared_data->sender_pid);
        printf("  Timestamp: %s", ctime(&shared_data->timestamp));
        
        // Detach and remove shared memory
        shmdt(shared_data);
        shmctl(shmid, IPC_RMID, NULL);
    }
    
    print_footer("SHARED MEMORY");
}
