#include "../include/ipc_common.h"

void print_header(const char *protocol) {
    printf("\n");
    printf("======================================\n");
    printf("DEMONSTRATING: %s\n", protocol);
    printf("======================================\n");
}

void print_footer(const char *protocol) {
    printf("======================================\n");
    printf("COMPLETED: %s\n", protocol);
    printf("======================================\n");
}

void delay_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

char* get_timestamp() {
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}
