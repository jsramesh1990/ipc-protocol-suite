
How to Build and Run::

# Clone the repository
git clone https://github.com/yourusername/ipc-protocol-suite.git
cd ipc-protocol-suite

# Build the project
make all

# Run the IPC demonstrations
./bin/ipc_suite

# Run tests
make test

# Build and run examples
gcc examples/producer_consumer.c -o producer_consumer -lrt
./producer_consumer
