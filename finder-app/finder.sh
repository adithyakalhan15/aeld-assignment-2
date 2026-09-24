#!/bin/sh

# Note: NO spaces around '='
filesdir=$1
searchstr=$2

# Note: Spaces AFTER '[' and BEFORE ']' are mandatory
if [ -z "$filesdir" ] || [ -z "$searchstr" ]; then
    echo "Error: Parameters not specified"
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "Error: Directory does not exist"
    exit 1
fi

X=$(find "$filesdir" -type f | wc -l)
Y=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"
