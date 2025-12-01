# IPC Protocol Suite in C

A comprehensive demonstration of Inter-Process Communication mechanisms in C, executed in sequence to show different IPC techniques.

## Features
- Multiple IPC mechanisms implemented sequentially
- Clean, modular C code
- Makefile for easy compilation
- Example applications
- Test scripts

## IPC Protocols Implemented
1. **Pipes** (Anonymous Pipes)
2. **FIFOs** (Named Pipes)
3. **Shared Memory**
4. **Message Queues**
5. **Semaphores**
6. **Sockets** (Unix Domain Sockets)
7. **Signals**

## Building
```bash
make all


# Build the project
make all

# Run the IPC demonstrations
./bin/ipc_suite

# Run tests
make test

# Build and run examples
gcc examples/producer_consumer.c -o producer_consumer -lrt
./producer_consumer

