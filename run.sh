#!/bin/bash

# Check if a day number is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <day_number>"
    exit 1
fi

if ! ./build.sh "$1"
then
    echo "Build process failed"
    exit 1
fi

echo "Running App"

./app