#!/bin/bash

# Check if a day number is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <day_number>"
    exit 1
fi

DAY_NUMBER=$1
DAY_FILE="day_${DAY_NUMBER}.cpp"

# Check if the specified day file exists
if [ ! -f "days/$DAY_FILE" ]; then
    echo "Error: File days/$DAY_FILE does not exist."
    exit 1
fi

# Compile the files
g++ -o main.o -c -Idays main.cpp
g++ -o day_${DAY_NUMBER}.o -c -Idays days/$DAY_FILE
g++ -o app main.o day_${DAY_NUMBER}.o

echo "Build successful! Run the app with ./app"
