# Inter-Process Communication (IPC) in Embedded Linux

## Overview

IPC (Inter-Process Communication) is the mechanism that allows:
- processes
- threads
- applications

to communicate and synchronize with each other.

IPC is essential in:
- Linux systems
- embedded Linux
- multitasking systems
- distributed applications

Without IPC:
- processes would be isolated
- no data sharing possible

---

# 1. What is IPC?

IPC means:

```text
Communication between independent processes
```

Processes can:
- exchange data
- synchronize execution
- send notifications

---

# 2. Why IPC is Needed

Modern Linux systems run:
- multiple applications
- services
- daemons
- device managers

These processes must:
- share data
- coordinate actions
- notify events

---

# 3. High-Level IPC Flow

```text
Process A
    ↓
IPC Mechanism
    ↓
Kernel Mediation
    ↓
Process B
``` id="flow1"

---

# 4. IPC Architecture

```text
+-------------------------+
| User Space              |
|-------------------------|
| Process A               |
| Process B               |
| Process C               |
+-------------------------+
| Linux Kernel IPC Layer  |
|-------------------------|
| Pipes                   |
| Message Queues          |
| Shared Memory           |
| Sockets                 |
| Semaphores              |
+-------------------------+
| Hardware                |
+-------------------------+
``` id="arch1"

---

# 5. IPC Mechanisms in Linux

| IPC Mechanism | Purpose |
|---------------|---------|
| Pipes | Parent-child communication |
| FIFOs | Named pipes |
| Message Queues | Structured messages |
| Shared Memory | Fast data sharing |
| Semaphores | Synchronization |
| Signals | Notifications |
| Sockets | Network/local communication |

---

# 6. Anonymous Pipes

Simple IPC between:
```text
parent and child processes
```

---

# 7. Pipe Flow

```text
Parent Process
      ↓
Pipe Buffer
      ↓
Child Process
``` id="pipe1"

---

# 8. Pipe Example

```c
int fd[2];

pipe(fd);
``` id="pipe2"

---

# 9. Pipe Characteristics

| Feature | Description |
|---------|-------------|
| Unidirectional | Yes |
| Parent-child only | Usually |
| Kernel buffer | Yes |

---

# 10. FIFO (Named Pipe)

FIFO =
```text
Named Pipe
```

Stored as filesystem object.

---

# 11. FIFO Creation

```bash
mkfifo myfifo
``` id="fifo1"

---

# 12. FIFO Flow

```text
Process A
    ↓
Named FIFO File
    ↓
Process B
``` id="fifo2"

---

# 13. Message Queues

Allow:
```text
structured message passing
```

between processes.

---

# 14. Message Queue Flow

```text
Sender Process
      ↓
Kernel Queue
      ↓
Receiver Process
``` id="msg1"

---

# 15. Message Queue Advantages

- asynchronous communication
- message prioritization
- structured data

---

# 16. POSIX Message Queue Example

```c
mq_open()
mq_send()
mq_receive()
``` id="msg2"

---

# 17. Shared Memory

Fastest IPC mechanism.

Processes share:
```text
same physical memory
```

---

# 18. Shared Memory Flow

```text
Process A
     ↘
 Shared Memory Region
     ↗
Process B
``` id="shm1"

---

# 19. Shared Memory Advantages

- extremely fast
- minimal copying
- efficient large data transfer

---

# 20. Shared Memory Disadvantages

Requires:
```text
explicit synchronization
```

---

# 21. Shared Memory Example

```c
shmget()
shmat()
``` id="shm2"

---

# 22. Shared Memory Lifecycle

```text
Create Shared Memory
        ↓
Attach to Process
        ↓
Read/Write Data
        ↓
Detach Memory
        ↓
Destroy Segment
``` id="shm3"

---

# 23. Semaphores

Used for:
```text
process synchronization
```

---

# 24. Semaphore Flow

```text
Process Requests Resource
         ↓
Semaphore Available?
     ↓ Yes       ↓ No
Continue         Wait
``` id="sem1"

---

# 25. Semaphore Operations

| Operation | Meaning |
|-----------|---------|
| wait/down | Acquire |
| signal/up | Release |

---

# 26. POSIX Semaphore Example

```c
sem_wait()
sem_post()
``` id="sem2"

---

# 27. Signals

Signals are:
```text
asynchronous notifications
```

sent to processes.

---

# 28. Common Signals

| Signal | Meaning |
|--------|---------|
| SIGINT | Interrupt |
| SIGKILL | Kill process |
| SIGTERM | Termination |
| SIGSEGV | Segmentation fault |

---

# 29. Signal Flow

```text
Kernel/Event
      ↓
Signal Sent
      ↓
Target Process
      ↓
Signal Handler
``` id="sig1"

---

# 30. Signal Example

```c
signal(SIGINT, handler);
``` id="sig2"

---

# 31. Socket IPC

Sockets allow:
- local IPC
- network communication

---

# 32. Socket Types

| Type | Purpose |
|------|---------|
| UNIX Domain Socket | Local IPC |
| TCP Socket | Network |
| UDP Socket | Datagram communication |

---

# 33. UNIX Domain Socket Flow

```text
Process A
     ↓
UNIX Socket
     ↓
Process B
``` id="sock1"

---

# 34. Socket Advantages

- flexible
- bidirectional
- network-capable

---

# 35. Socket API

```c
socket()
bind()
listen()
accept()
connect()
``` id="sock2"

---

# 36. mmap-based IPC

Processes map:
```text
same file/device memory
```

into address space.

---

# 37. mmap IPC Flow

```text
Shared File
    ↓
Mapped Into Multiple Processes
``` id="mmap1"

---

# 38. IPC in Embedded Linux

Embedded systems use IPC for:
- daemon communication
- hardware services
- multimedia pipelines
- RT systems

---

# 39. Example Embedded IPC

```text
Application
     ↓
IPC
     ↓
Hardware Service Daemon
     ↓
Device Driver
``` id="emb1"

---

# 40. IPC and Kernel Space

Kernel provides:
- IPC APIs
- synchronization
- buffering
- protection

---

# 41. Synchronization in IPC

Shared resources require:
- semaphores
- mutexes
- atomics

---

# 42. Producer-Consumer Example

```text
Producer Process
       ↓
Shared Queue
       ↓
Consumer Process
``` id="prod1"

---

# 43. Blocking vs Non-Blocking IPC

| Type | Behavior |
|------|----------|
| Blocking | Waits for event |
| Non-blocking | Returns immediately |

---

# 44. IPC Performance Comparison

| IPC Method | Speed |
|------------|------|
| Shared Memory | Fastest |
| Pipes | Medium |
| Message Queue | Medium |
| Sockets | Slower |

---

# 45. Kernel IPC Internals

Linux kernel manages:
- buffers
- queues
- scheduling
- synchronization

---

# 46. IPC Security

Kernel ensures:
- process isolation
- permissions
- access control

---

# 47. Viewing IPC Objects

---

## Shared Memory

```bash
ipcs -m
``` id="ipcs1"

---

## Semaphores

```bash
ipcs -s
``` id="ipcs2"

---

## Message Queues

```bash
ipcs -q
``` id="ipcs3"

---

# 48. Removing IPC Objects

```bash
ipcrm
``` id="ipcrm1"

---

# 49. Common IPC Problems

| Problem | Description |
|---------|-------------|
| Deadlock | Processes wait forever |
| Race condition | Data corruption |
| Buffer overflow | Excess data |
| Resource leak | IPC object not removed |

---

# 50. Deadlock Example

```text
Process A waits B
Process B waits A
``` id="dead1"

---

# 51. IPC in Real-Time Systems

RT systems require:
- low latency
- deterministic communication
- minimal copying

Shared memory commonly used.

---

# 52. D-Bus in Embedded Linux

Common IPC framework in Linux.

Used by:
- systemd
- desktop services
- embedded middleware

---

# 53. D-Bus Architecture

```text
Application A
      ↓
D-Bus Daemon
      ↓
Application B
``` id="dbus1"

---

# 54. IPC Selection Guidelines

| Requirement | Preferred IPC |
|-------------|---------------|
| Fastest communication | Shared memory |
| Simple parent-child | Pipe |
| Network communication | Socket |
| Structured messages | Message Queue |

---

# 55. IPC Debugging

---

## Trace IPC

```bash
strace
``` id="dbg1"

---

## Monitor Processes

```bash
top
``` id="dbg2"

---

## IPC Resources

```bash
ipcs
``` id="dbg3"

---

# 56. Complete IPC Workflow

```text
Process Creates IPC Object
          ↓
Kernel Allocates Resource
          ↓
Processes Exchange Data
          ↓
Synchronization Applied
          ↓
IPC Object Destroyed
``` id="final1"

---

# 57. Advantages of IPC

- process cooperation
- modular software design
- multitasking support
- efficient communication

---

# 58. Disadvantages

- synchronization complexity
- overhead
- deadlock risk
- debugging difficulty

---

# 59. Summary

- IPC enables communication between processes
- Linux supports multiple IPC mechanisms
- Shared memory is fastest IPC
- Pipes and sockets widely used
- Synchronization critical for IPC safety
- Essential in embedded Linux systems

---

````
