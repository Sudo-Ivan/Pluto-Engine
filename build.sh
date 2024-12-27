#!/bin/bash

# Build all examples
make clean
make

# List available examples
echo "Available examples:"
echo "------------------"
for file in build/*; do
    if [ -x "$file" ] && [ ! -d "$file" ]; then  # Check if file is executable and not a directory
        echo "$(basename "$file")"
    fi
done
echo "------------------"

# Get user selection
echo "Enter example name to run (or 'q' to quit):"
read selection

if [ "$selection" = "q" ]; then
    echo "Exiting..."
    exit 0
fi

# Check if selection exists and is executable
if [ -x "build/$selection" ]; then
    echo "Running $selection..."
    "./build/$selection"
else
    echo "Error: '$selection' not found or not executable"
    exit 1
fi 