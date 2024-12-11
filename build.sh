#!/bin/bash

# Check if a day number is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <day_number>"
    exit 1
fi

DAY_NUMBER=$1
DAY_FILE="day_$DAY_NUMBER.cpp"

# Check if the specified day file exists
if [ ! -f "days/$DAY_FILE" ]; then
    echo "Error: File days/$DAY_FILE does not exist."
    exit 1
fi

# Compile the files
if ! g++ -o main.o -m64 -g -c -Idays -Iutils main.cpp
then
    echo "Main compilation failed"
    exit 1
fi
if ! g++ -o utils.o -m64 -g -c  -Idays -Iutils utils/utils.cpp
then
    echo "Utils compilation failed"
    exit 1
fi
if ! g++ -o day_"$DAY_NUMBER".o -m64 -g -c  -Idays -Iutils days/"$DAY_FILE"
then
    echo "Day $DAY_NUMBER compilation failed"
    exit 1
fi
if ! g++ -m64 -o app main.o day_"$DAY_NUMBER".o utils.o
then
    echo "Linking failed"
    exit 1
fi
echo "Build successful!"