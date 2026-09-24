#!/bin/sh

writefile=$1
writestr=$2

# Check if both arguments were provided
if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Parameters not specified"
    exit 1
fi

# Create directory path if it does not exist
mkdir -p "$(dirname "$writefile")"

# Write to file
echo "$writestr" > "$writefile"

# Check if file creation worked
if [ $? -ne 0 ]; then
    echo "Error: Could not create file"
    exit 1
fi


