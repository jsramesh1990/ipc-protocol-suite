#!/bin/bash

echo "Running IPC Protocol Suite Tests"
echo "================================"

# Make sure we're in the right directory
cd "$(dirname "$0")/.."

# Build the project
make clean
make all

# Run the main program
echo -e "\nRunning IPC demonstrations..."
./bin/ipc_suite

# Clean up
make clean

echo -e "\nAll tests completed!"
