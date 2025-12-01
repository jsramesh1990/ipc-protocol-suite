#include "../include/ipc_common.h"
#include <sys/ipc.h>
#include <sys/sem.h>

// Union for semctl
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void demo_semaphores() {
    print_header("SEMAPHORES");
    
    int semid;
    union semun arg;
    struct sembuf sb;
    
    // Create semaphore set
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    
    // Initialize semaphore to 1
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process
        printf("Child waiting for semaphore...\n");
        
        // Wait on semaphore (P operation)
        sb.sem_num = 0;
        sb.sem_op = -1; // Decrement
        sb.sem_flg = 0;
        
        semop(semid, &sb, 1);
        
        printf("Child acquired semaphore\n");
        printf("Child: Critical section\n");
        sleep(1);
        
        // Release semaphore (V operation)
        sb.sem_op = 1; // Increment
        semop(semid, &sb, 1);
        
        printf("Child released semaphore\n");
        exit(0);
    }
    else if (pid > 0) { // Parent process
        sleep(1); // Let child go first
        
        printf("Parent waiting for semaphore...\n");
        
        sb.sem_num = 0;
        sb.sem_op = -1;
        sb.sem_flg = 0;
        
        semop(semid, &sb, 1);
        
        printf("Parent acquired semaphore\n");
        printf("Parent: Critical section\n");
        sleep(1);
        
        sb.sem_op = 1;
        semop(semid, &sb, 1);
        
        printf("Parent released semaphore\n");
        
        wait(NULL);
        
        // Remove semaphore
        semctl(semid, 0, IPC_RMID);
    }
    
    print_footer("SEMAPHORES");
}
