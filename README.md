# IPC Protocol Suite in C

![C](https://img.shields.io/badge/Language-C-blue.svg)
![IPC](https://img.shields.io/badge/IPC-Protocol_Suite-green.svg)
![POSIX](https://img.shields.io/badge/Standard-POSIX-orange.svg)
![Build](https://img.shields.io/badge/Build-Make-success.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Version](https://img.shields.io/badge/Version-1.0-red.svg)
![Cross-Platform](https://img.shields.io/badge/Platform-Linux_|_Unix-lightgrey.svg)

A comprehensive demonstration of Inter-Process Communication (IPC) mechanisms in C, providing a complete suite of IPC techniques with clean, modular implementations and executable examples.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [IPC Mechanisms](#ipc-mechanisms-implemented)
- [System Architecture](#system-architecture)
- [IPC Communication Flow](#ipc-communication-flow)
- [Individual IPC Working Flows](#individual-ipc-working-flows)
- [Orchestrator Flow](#orchestrator-flow)
- [Prerequisites](#prerequisites)
- [Quick Start](#quick-start)
- [Building the Project](#building-the-project)
- [Running IPC Demonstrations](#running-ipc-demonstrations)
- [Individual Mechanism Examples](#individual-mechanism-examples)
- [Project Structure](#project-structure)
- [IPC Mechanism Comparison](#ipc-mechanism-comparison)
- [Testing](#testing)
- [Performance Metrics](#performance-metrics)
- [Troubleshooting](#troubleshooting)
- [Use Cases](#use-cases)
- [Extending the Project](#extending-the-project)
- [License](#license)

## Overview

The IPC Protocol Suite demonstrates all major Inter-Process Communication mechanisms available in UNIX/Linux systems. Each mechanism is implemented with clean, well-documented C code and can be executed independently or as part of the complete suite.

### Why IPC?
- **Data Sharing**: Allow processes to exchange information
- **Resource Sharing**: Enable multiple processes to access shared resources
- **Process Synchronization**: Coordinate process execution and prevent race conditions
- **Modularity**: Break complex systems into smaller, communicating processes

## Features

- ✅ **7 IPC Mechanisms** implemented sequentially
- ✅ **Clean, modular C code** with header files
- ✅ **Comprehensive Makefile** for easy compilation
- ✅ **Example applications** for each mechanism
- ✅ **Test scripts** for validation
- ✅ **Orchestrator** to run all mechanisms in sequence
- ✅ **POSIX compliant** - works on all Linux/Unix systems

## IPC Mechanisms Implemented

| # | Mechanism | Type | Persistence | Speed | Use Case |
|---|-----------|------|-------------|-------|----------|
| 1 | **Pipes** | Anonymous | Process-based | Fast | Parent-Child communication |
| 2 | **FIFOs** | Named Pipes | Filesystem | Fast | Unrelated processes |
| 3 | **Shared Memory** | Memory-mapped | System | Very Fast | Large data exchange |
| 4 | **Message Queues** | Message-based | System | Moderate | Structured messages |
| 5 | **Semaphores** | Synchronization | System | Fast | Resource locking |
| 6 | **Unix Sockets** | Bidirectional | Filesystem | Fast | Two-way communication |
| 7 | **Signals** | Asynchronous | Process-based | Immediate | Event notification |

## System Architecture

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           IPC PROTOCOL SUITE                                  │
│                                                                               │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │                         IPC ORCHESTRATOR                             │   │
│  │                    (Coordinate all IPC mechanisms)                    │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
│                                    │                                         │
│                                    │ Sequential Execution                    │
│                                    ▼                                         │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │                        IPC MECHANISMS                                 │   │
│  ├───────────────┬───────────────┬───────────────┬───────────────────┤   │
│  │    PIPE       │    FIFO       │ SHARED MEM    │  MSG QUEUE        │   │
│  │  (Anonymous)  │  (Named Pipe) │  (shm_open)   │  (mq_open)        │   │
│  ├───────────────┼───────────────┼───────────────┼───────────────────┤   │
│  │  SEMAPHORE    │   SOCKETS     │   SIGNALS     │                   │   │
│  │  (sem_open)   │ (Unix Domain) │  (signal)     │                   │   │
│  └───────────────┴───────────────┴───────────────┴───────────────────┘   │
│                                    │                                         │
│                                    ▼                                         │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │                      DEMONSTRATION OUTPUT                            │   │
│  │  - Success/Failure messages                                          │   │
│  │  - Data transfer verification                                        │   │
│  │  - Timing metrics                                                    │   │
│  │  - Error handling                                                    │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────────────────┘
```

## IPC Communication Flow

### Overall Orchestrator Flow

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                         IPC ORCHESTRATOR FLOW                                │
└─────────────────────────────────────────────────────────────────────────────┘

    START
      │
      ▼
┌─────────────────┐
│ Initialize IPC  │
│   Framework     │
└────────┬────────┘
         │
         ▼
┌─────────────────┐     ┌─────────────────┐
│  1. PIPE Demo   │────►│  Pipe Created   │
│ (Anonymous)     │     │  Data Written   │
└────────┬────────┘     │  Data Read      │
         │              └─────────────────┘
         ▼
┌─────────────────┐     ┌─────────────────┐
│  2. FIFO Demo   │────►│  FIFO Created   │
│ (Named Pipe)    │     │  Writer/Reader  │
└────────┬────────┘     └─────────────────┘
         │
         ▼
┌─────────────────┐     ┌─────────────────┐
│  3. Shared Mem  │────►│  Memory Mapped  │
│   Demo          │     │  Data Written   │
└────────┬────────┘     │  Data Read      │
         │              └─────────────────┘
         ▼
┌─────────────────┐     ┌─────────────────┐
│  4. Msg Queue   │────►│  Queue Created  │
│   Demo          │     │  Msg Sent/Recv  │
└────────┬────────┘     └─────────────────┘
         │
         ▼
┌─────────────────┐     ┌─────────────────┐
│  5. Semaphore   │────►│  Semaphore Init │
│   Demo          │     │  Wait/Post Ops  │
└────────┬────────┘     └─────────────────┘
         │
         ▼
┌─────────────────┐     ┌─────────────────┐
│  6. Socket      │────►│  Socket Created │
│   Demo          │     │  Client-Server  │
└────────┬────────┘     └─────────────────┘
         │
         ▼
┌─────────────────┐     ┌─────────────────┐
│  7. Signals     │────►│  Handler Reg    │
│   Demo          │     │  Signal Sent    │
└────────┬────────┘     └─────────────────┘
         │
         ▼
┌─────────────────┐
│  Cleanup & Exit │
└─────────────────┘
```

## Individual IPC Working Flows

### 1. PIPE (Anonymous Pipe) Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                         PIPE MECHANISM                           │
└─────────────────────────────────────────────────────────────────┘

    PROCESS                                    PROCESS
    (PARENT)                                    (CHILD)
       │                                           │
       │  pipe(fd) - Create pipe                   │
       │  (fd[0]=read, fd[1]=write)                │
       │                                           │
       │  fork() - Create child                    │
       │                                           │
       │  close(fd[0]) - Close read end            │
       │                                           │
       │  write(fd[1], "data")                     │
       │──────────────────────────────────────────►│
       │                                           │
       │                                           │ close(fd[1])
       │                                           │
       │                                           │ read(fd[0])
       │                                           │
       │                                           │ Process data
       │                                           │
       │  wait() - Wait for child                  │
       │◄──────────────────────────────────────────│ exit()
       │                                           │
       ▼                                           ▼
```

### 2. FIFO (Named Pipe) Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                         FIFO MECHANISM                           │
└─────────────────────────────────────────────────────────────────┘

    WRITER PROCESS                            READER PROCESS
         │                                         │
         │  mkfifo("/tmp/myfifo", 0666)            │
         │  (Create named pipe)                    │
         │                                         │
         │  open(fifo, O_WRONLY)                   │  open(fifo, O_RDONLY)
         │                                         │
         │  write("Hello")                         │
         │────────────────────────────────────────►│
         │                                         │  read(buffer)
         │                                         │
         │                                         │  printf("%s", buffer)
         │                                         │
         │  close(fd)                              │  close(fd)
         │                                         │
         │  unlink(fifo) - Remove                  │
         ▼                                         ▼
```

### 3. Shared Memory Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                      SHARED MEMORY FLOW                          │
└─────────────────────────────────────────────────────────────────┘

    PROCESS A                                 PROCESS B
         │                                         │
         │  shm_open("/shared", O_CREAT|O_RDWR)   │
         │                                         │
         │  ftruncate(shm_fd, size)                │
         │                                         │
         │  mmap(NULL, size, PROT_READ|PROT_WRITE) │
         │                                         │
         │  ptr = mapped memory                    │
         │                                         │
         │  strcpy(ptr, "Data")                    │  shm_open("/shared", O_RDWR)
         │                                         │
         │                                         │  mmap(NULL, size, PROT_READ)
         │                                         │
         │                                         │  printf("%s", ptr)
         │                                         │
         │  msync(ptr, size, MS_SYNC)              │
         │                                         │
         │  munmap(ptr, size)                      │  munmap(ptr, size)
         │                                         │
         │  shm_unlink("/shared")                  │
         ▼                                         ▼
```

### 4. Message Queue Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                     MESSAGE QUEUE FLOW                           │
└─────────────────────────────────────────────────────────────────┘

    SENDER PROCESS                            RECEIVER PROCESS
         │                                         │
         │  mq_open("/mq", O_CREAT|O_WRONLY)      │  mq_open("/mq", O_RDONLY)
         │                                         │
         │  mq_send(mq, msg, len, priority)       │
         │────────────────────────────────────────►│
         │                                         │  mq_receive(mq, buffer, len, &prio)
         │                                         │
         │  Send another message                   │  Process message
         │────────────────────────────────────────►│
         │                                         │  mq_receive()
         │                                         │
         │  mq_close(mq)                           │  mq_close(mq)
         │                                         │
         │  mq_unlink("/mq")                       │
         ▼                                         ▼
```

### 5. Semaphore Flow (Synchronization)

```
┌─────────────────────────────────────────────────────────────────┐
│                       SEMAPHORE FLOW                             │
└─────────────────────────────────────────────────────────────────┘

    PROCESS A (Lock)                          PROCESS B (Wait)
         │                                         │
         │  sem_open("/sem", O_CREAT, 0644, 1)    │  sem_open("/sem", 0)
         │                                         │
         │  sem_wait(sem) - Lock acquired         │
         │  (Critical Section)                    │
         │                                         │  sem_wait(sem) - BLOCKS
         │  Access shared resource                │         │
         │                                         │         │
         │  sem_post(sem) - Release lock          │         │
         │────────────────────────────────────────►│         │
         │                                         │  sem_wait() - Now acquires
         │                                         │         │
         │                                         │  Access resource
         │                                         │         │
         │                                         │  sem_post(sem)
         │                                         │
         ▼                                         ▼
```

### 6. Unix Domain Socket Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                      UNIX SOCKET FLOW                            │
└─────────────────────────────────────────────────────────────────┘

    SERVER                                        CLIENT
      │                                             │
      │  socket(AF_UNIX, SOCK_STREAM, 0)           │  socket(AF_UNIX, SOCK_STREAM, 0)
      │                                             │
      │  bind(sockfd, &addr, sizeof(addr))         │
      │                                             │
      │  listen(sockfd, 5)                         │
      │                                             │  connect(sockfd, &addr, sizeof(addr))
      │                                             │─────────┐
      │  accept() - New connection                 │         │
      │◄────────────────────────────────────────────│         │
      │                                             │         │
      │  read(newfd, buffer, size)                 │  write(sockfd, "Hello", 5)
      │◄────────────────────────────────────────────│         │
      │                                             │         │
      │  write(newfd, "World", 5)                  │  read(sockfd, buffer, size)
      │─────────────────────────────────────────────►│         │
      │                                             │         │
      │  close(newfd)                              │  close(sockfd)
      │                                             │
      │  unlink(socket_path)                       │
      ▼                                             ▼
```

### 7. Signal Flow (Asynchronous)

```
┌─────────────────────────────────────────────────────────────────┐
│                         SIGNAL FLOW                              │
└─────────────────────────────────────────────────────────────────┘

    PROCESS A                                    PROCESS B
      │                                             │
      │  signal(SIGUSR1, handler)                  │
      │  (Register handler)                        │
      │                                             │
      │  Handler function defined:                 │
      │  void handler(int sig) {                   │
      │      printf("Signal received\n");          │
      │  }                                         │
      │                                             │
      │                                             │  kill(pid_A, SIGUSR1)
      │                                             │─────────┐
      │◄────────────────────────────────────────────│         │
      │                                             │         │
      │  Handler executes immediately               │         │
      │  (Anywhere in code)                         │         │
      │                                             │         │
      │  printf("Signal received")                 │         │
      │                                             │         │
      │  Return to normal execution                 │         │
      │                                             │         │
      ▼                                             ▼
```

## Orchestrator Flow

```
                    ┌─────────────────────┐
                    │   IPC Orchestrator  │
                    │   ./bin/ipc_suite   │
                    └──────────┬──────────┘
                               │
                               ▼
              ╔═══════════════════════════════╗
              ║   Initialization & Validation  ║
              ╚═══════════════════════════════╝
                               │
                               ▼
         ┌─────────────────────────────────────────┐
         │         Sequential Execution            │
         ├─────────────────────────────────────────┤
         │                                         │
         │  ┌────────────────────────────────┐    │
         │  │ PIPE TEST                       │    │
         │  │ ✓ Pipe created                  │    │
         │  │ ✓ Data written: "Hello Pipe"    │    │
         │  │ ✓ Data read: "Hello Pipe"       │    │
         │  │ ✓ Test PASSED                   │    │
         │  └────────────────────────────────┘    │
         │                    │                    │
         │                    ▼                    │
         │  ┌────────────────────────────────┐    │
         │  │ FIFO TEST                       │    │
         │  │ ✓ FIFO created at /tmp/myfifo   │    │
         │  │ ✓ Writer sent: "FIFO Message"   │    │
         │  │ ✓ Reader received: "FIFO Msg"   │    │
         │  │ ✓ Test PASSED                   │    │
         │  └────────────────────────────────┘    │
         │                    │                    │
         │                    ▼                    │
         │  ┌────────────────────────────────┐    │
         │  │ SHARED MEMORY TEST              │    │
         │  │ ✓ Shared memory created (4096) │    │
         │  │ ✓ Data written: "Shared Data"  │    │
         │  │ ✓ Data read: "Shared Data"     │    │
         │  │ ✓ Test PASSED                  │    │
         │  └────────────────────────────────┘    │
         │                    │                    │
         │                    ▼                    │
         │  ┌────────────────────────────────┐    │
         │  │ MESSAGE QUEUE TEST              │    │
         │  │ ✓ Queue created: /msgqueue     │    │
         │  │ ✓ Message sent: "Queue Msg"    │    │
         │  │ ✓ Message received: "Queue Msg"│    │
         │  │ ✓ Test PASSED                  │    │
         │  └────────────────────────────────┘    │
         │                    │                    │
         │                    ▼                    │
         │  ┌────────────────────────────────┐    │
         │  │ SEMAPHORE TEST                  │    │
         │  │ ✓ Semaphore created: /sem      │    │
         │  │ ✓ Lock acquired                │    │
         │  │ ✓ Critical section executed    │    │
         │  │ ✓ Lock released                │    │
         │  │ ✓ Test PASSED                  │    │
         │  └────────────────────────────────┘    │
         │                    │                    │
         │                    ▼                    │
         │  ┌────────────────────────────────┐    │
         │  │ SOCKET TEST                     │    │
         │  │ ✓ Unix socket created          │    │
         │  │ ✓ Server bound to /tmp/socket  │    │
         │  │ ✓ Client connected             │    │
         │  │ ✓ Data exchanged: "Ping-Pong"  │    │
         │  │ ✓ Test PASSED                  │    │
         │  └────────────────────────────────┘    │
         │                    │                    │
         │                    ▼                    │
         │  ┌────────────────────────────────┐    │
         │  │ SIGNAL TEST                     │    │
         │  │ ✓ Signal handler registered    │    │
         │  │ ✓ SIGUSR1 sent to process      │    │
         │  │ ✓ Handler executed              │    │
         │  │ ✓ Test PASSED                  │    │
         │  └────────────────────────────────┘    │
         │                                         │
         └─────────────────────────────────────────┘
                               │
                               ▼
              ╔═══════════════════════════════╗
              ║     Cleanup & Resource Free   ║
              ║  - Close file descriptors     ║
              ║  - Unlink FIFOs               ║
              ║  - Unlink shared memory       ║
              ║  - Close message queues       ║
              ║  - Unlink semaphores         ║
              ║  - Close sockets              ║
              ╚═══════════════════════════════╝
                               │
                               ▼
                    ┌─────────────────────┐
                    │  EXIT (SUCCESS)     │
                    └─────────────────────┘
```

## Prerequisites

### System Requirements
- **Operating System**: Linux/Unix (Ubuntu, Debian, CentOS, macOS)
- **Compiler**: GCC 4.8+ with POSIX support
- **Libraries**: POSIX real-time extensions (librt)
- **Build Tool**: GNU Make 3.81+

### Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install manpages-posix-dev
```

**CentOS/RHEL:**
```bash
sudo yum groupinstall "Development Tools"
sudo yum install glibc-devel
```

**macOS:**
```bash
xcode-select --install
```

## Quick Start

```bash
# Clone the repository
git clone https://github.com/jsramesh1990/ipc-protocol-suite.git
cd ipc-protocol-suite

# Build everything
make all

# Run all IPC demonstrations
./bin/ipc_suite

# Run specific test
make test
```

## Building the Project

### Build Commands

```bash
# Build all components
make all

# Build specific components
make ipc_suite      # Build main orchestrator
make examples       # Build example applications
make clean          # Remove compiled files

# Full rebuild
make clean && make all
```

### Build Output

```
gcc -Wall -Wextra -O2 -c src/ipc_pipe.c -o obj/ipc_pipe.o
gcc -Wall -Wextra -O2 -c src/ipc_fifo.c -o obj/ipc_fifo.o
gcc -Wall -Wextra -O2 -c src/ipc_shm.c -o obj/ipc_shm.o
gcc -Wall -Wextra -O2 -c src/ipc_mq.c -o obj/ipc_mq.o
gcc -Wall -Wextra -O2 -c src/ipc_sem.c -o obj/ipc_sem.o
gcc -Wall -Wextra -O2 -c src/ipc_socket.c -o obj/ipc_socket.o
gcc -Wall -Wextra -O2 -c src/ipc_signal.c -o obj/ipc_signal.o
gcc -Wall -Wextra -O2 -c src/ipc_orchestrator.c -o obj/ipc_orchestrator.o
gcc obj/*.o -o bin/ipc_suite -lrt -lpthread
Build successful!
```

## Running IPC Demonstrations

### Run All Mechanisms
```bash
./bin/ipc_suite
```

**Expected Output:**
```
========================================
   IPC PROTOCOL SUITE DEMONSTRATION
========================================

[1/7] Testing PIPE...
  ✓ Pipe created successfully
  ✓ Data written: "Hello from Parent!"
  ✓ Data read: "Hello from Parent!"
  ✓ PIPE test PASSED

[2/7] Testing FIFO...
  ✓ FIFO created at /tmp/myfifo
  ✓ Writer process sent: "FIFO Message"
  ✓ Reader received: "FIFO Message"
  ✓ FIFO test PASSED

[3/7] Testing SHARED MEMORY...
  ✓ Shared memory created (size: 4096)
  ✓ Data written: "Shared Memory Data"
  ✓ Data read: "Shared Memory Data"
  ✓ SHARED MEMORY test PASSED

[4/7] Testing MESSAGE QUEUE...
  ✓ Message queue created: /msgqueue
  ✓ Message sent: "Hello Queue"
  ✓ Message received: "Hello Queue"
  ✓ MESSAGE QUEUE test PASSED

[5/7] Testing SEMAPHORE...
  ✓ Semaphore created: /mysem
  ✓ Lock acquired
  ✓ Critical section executed
  ✓ Lock released
  ✓ SEMAPHORE test PASSED

[6/7] Testing UNIX SOCKET...
  ✓ Socket created
  ✓ Server bound to /tmp/ipc_socket
  ✓ Client connected
  ✓ Server sent: "Hello from Server"
  ✓ Client received: "Hello from Server"
  ✓ SOCKET test PASSED

[7/7] Testing SIGNAL...
  ✓ Signal handler registered for SIGUSR1
  ✓ Signal sent to process
  ✓ Handler executed: "Received SIGUSR1"
  ✓ SIGNAL test PASSED

========================================
   ALL TESTS PASSED SUCCESSFULLY!
========================================
```

## Individual Mechanism Examples

### PIPE Example
```c
// Simple pipe communication
int fd[2];
pipe(fd);
if (fork() == 0) {
    close(fd[1]);
    read(fd[0], buffer, sizeof(buffer));
} else {
    close(fd[0]);
    write(fd[1], "Hello", 5);
}
```

### FIFO Example
```bash
# Terminal 1 (Writer)
./bin/fifo_writer

# Terminal 2 (Reader)
./bin/fifo_reader
```

### Shared Memory with Semaphore
```bash
# Producer-Consumer example
./bin/producer_consumer
```

### Message Queue Example
```bash
# Send message
./bin/mq_send "Hello World"

# Receive message
./bin/mq_receive
```

## Project Structure

```
ipc-protocol-suite/
│
├── bin/                        # Compiled binaries
│   └── ipc_suite              # Main orchestrator
│
├── src/                        # Source code files
│   ├── ipc_pipe.c             # Anonymous pipe implementation
│   ├── ipc_fifo.c             # Named pipe (FIFO) implementation
│   ├── ipc_shm.c              # Shared memory implementation
│   ├── ipc_mq.c               # Message queue implementation
│   ├── ipc_sem.c              # Semaphore implementation
│   ├── ipc_socket.c           # Unix domain socket implementation
│   ├── ipc_signal.c           # Signal handling implementation
│   └── ipc_orchestrator.c     # Main orchestrator
│
├── include/                    # Header files
│   ├── ipc_common.h           # Common definitions
│   ├── ipc_pipe.h             # Pipe declarations
│   ├── ipc_fifo.h             # FIFO declarations
│   ├── ipc_shm.h              # Shared memory declarations
│   ├── ipc_mq.h               # Message queue declarations
│   ├── ipc_sem.h              # Semaphore declarations
│   ├── ipc_socket.h           # Socket declarations
│   └── ipc_signal.h           # Signal declarations
│
├── obj/                        # Object files (generated)
│   └── *.o                    # Compiled objects
│
├── examples/                   # Example applications
│   ├── producer_consumer.c    # Producer-Consumer with semaphores
│   ├── chat_server.c          # Socket chat server
│   ├── chat_client.c          # Socket chat client
│   └── signal_demo.c          # Signal demonstration
│
├── tests/                      # Test scripts
│   ├── test_pipe.sh
│   ├── test_fifo.sh
│   ├── test_shm.sh
│   └── test_all.sh
│
├── Makefile                    # Build automation
└── README.md                   # Documentation
```

## IPC Mechanism Comparison

| Feature | Pipe | FIFO | Shared Mem | Msg Queue | Semaphore | Socket | Signal |
|---------|------|------|------------|-----------|-----------|--------|---------|
| **Data Type** | Byte stream | Byte stream | Memory block | Structured | Counter | Byte stream | Event |
| **Direction** | Unidirectional | Unidirectional | Bidirectional | Unidirectional | N/A | Bidirectional | N/A |
| **Speed** | Fast | Fast | Very Fast | Moderate | Fast | Moderate | Immediate |
| **Persistence** | Process | Filesystem | System | System | System | Filesystem | Process |
| **Related Processes** | Parent-Child | Any | Any | Any | Any | Any | Any |
| **Blocking** | Yes | Yes | No | Yes | Yes | Yes | No |
| **Kernel Involvement** | High | High | Low | High | Medium | High | Low |
| **Use Case** | Simple comm | Named pipes | Large data | Messages | Sync | Network | Events |

## Testing

### Run All Tests
```bash
make test
```

### Individual Tests
```bash
# Test pipe mechanism
./tests/test_pipe.sh

# Test FIFO mechanism
./tests/test_fifo.sh

# Test shared memory
./tests/test_shm.sh

# Run with valgrind (memory leak check)
valgrind --leak-check=full ./bin/ipc_suite
```

### Test Coverage
```bash
# Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage src/*.c -o bin/ipc_suite -lrt -lpthread

# Run tests
./bin/ipc_suite

# Generate coverage report
gcov src/*.c
```

## Performance Metrics

| Mechanism | Latency (μs) | Bandwidth (MB/s) | Max Size | Overhead |
|-----------|-------------|------------------|----------|----------|
| Pipe | 2-5 | 100-200 | 64KB | Low |
| FIFO | 3-6 | 80-150 | 64KB | Low |
| Shared Memory | 0.5-1 | 1000+ | System limit | Very Low |
| Message Queue | 5-10 | 50-100 | 8192 bytes | Medium |
| Semaphore | 1-2 | N/A | N/A | Low |
| Unix Socket | 4-8 | 200-400 | 64KB | Medium |
| Signal | <1 | N/A | N/A | Very Low |

## Troubleshooting

| Issue | Solution |
|-------|----------|
| **IPC resource limit reached** | Check limits: `ipcs -l`<br/>Increase limits: `ulimit -l unlimited` |
| **Permission denied** | Run with appropriate permissions: `sudo ./bin/ipc_suite` |
| **File exists error** | Clean up stale IPC objects: `ipcrm -a` |
| **MQ_OPEN failed** | Ensure mqueue fs mounted: `mount -t mqueue none /dev/mqueue` |
| **Semaphore exists** | Remove semaphore: `sem_unlink("/sem_name")` |
| **Shared memory busy** | Remove: `ipcrm -m <shmid>` |
| **Signal handler not called** | Check signal mask: `sigprocmask()` |
| **Socket address in use** | Remove socket file: `rm /tmp/ipc_socket` |

### Debug Build
```bash
# Build with debug symbols
make clean
make CFLAGS="-g -O0 -DDEBUG"

# Run with gdb
gdb ./bin/ipc_suite
```

## Use Cases

### When to Use Each IPC

**PIPE:**
- Parent-child process communication
- Command pipelines (`ls | grep "txt"`)
- Simple one-way data flow

**FIFO:**
- Unrelated process communication
- Logging systems
- Data streaming between services

**Shared Memory:**
- High-performance data exchange
- Database caches
- Real-time systems
- Large data transfers

**Message Queues:**
- Priority-based messaging
- Client-server applications
- Task distribution systems
- Asynchronous communication

**Semaphores:**
- Resource access synchronization
- Producer-Consumer problems
- Mutual exclusion
- Thread/process coordination

**Unix Sockets:**
- Bi-directional communication
- Desktop applications (X11, Wayland)
- System daemons
- Local RPC

**Signals:**
- Process termination handling
- Timer events
- Asynchronous notifications
- Error recovery

## Extending the Project

### Adding New IPC Mechanism

1. **Create header file** (`include/ipc_new.h`):
```c
#ifndef IPC_NEW_H
#define IPC_NEW_H
int test_new_mechanism(void);
#endif
```

2. **Create implementation** (`src/ipc_new.c`):
```c
#include "ipc_new.h"
#include "ipc_common.h"

int test_new_mechanism(void) {
    printf("Testing NEW mechanism...\n");
    // Implementation
    return SUCCESS;
}
```

3. **Update orchestrator** (`src/ipc_orchestrator.c`):
```c
#include "ipc_new.h"
// Call test_new_mechanism() in main()
```

4. **Update Makefile**:
```makefile
OBJECTS += obj/ipc_new.o
```

### Benchmark Suite
```c
// Add timing measurements
#include <sys/time.h>

struct timeval start, end;
gettimeofday(&start, NULL);
// IPC operation
gettimeofday(&end, NULL);
long elapsed = (end.tv_sec - start.tv_sec) * 1000000 + 
               (end.tv_usec - start.tv_usec);
printf("Time: %ld μs\n", elapsed);
```

## License

MIT License - Free to use, modify, and distribute for learning and research purposes.

---

## Acknowledgments

- POSIX Standards Documentation
- The Linux Programming Interface (Michael Kerrisk)
- Operating Systems: Three Easy Pieces

---

<div align="center">
Made with ❤️ for Systems Programming Education
</div>
