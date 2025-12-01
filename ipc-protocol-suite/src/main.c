#include "../include/ipc_common.h"
#include "../include/shared_data.h"

// External function declarations
void demo_pipes();
void demo_fifos();
void demo_shared_memory();
void demo_message_queue();
void demo_semaphores();
void demo_sockets();
void demo_signals();

int main() {
    printf("=== IPC Protocol Suite Demonstration ===\n\n");
    
    // Execute IPC demos in sequence
    demo_pipes();
    demo_fifos();
    demo_shared_memory();
    demo_message_queue();
    demo_semaphores();
    demo_sockets();
    demo_signals();
    
    printf("\n=== All IPC demonstrations completed ===\n");
    return 0;
}
