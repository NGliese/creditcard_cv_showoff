#!/bin/bash

# Capture the start time
start_time=$(date +%s)

# Find all C++ files in the root folder and subfolders, excluding the "build" directory
cpp_files=$(find . -name "*.cpp" -o -name "*.hpp" -not -path "./main/Components/build/*" -not -path "./build/*" )

# Loop through each C++ file and run clang-format to prettify it
for file in $cpp_files; do
    clang-format -style=Google -i $file
done

# Capture the end time
end_time=$(date +%s)

# Calculate the time difference
time_taken=$((end_time - start_time))

# Print the time it took to run the script
echo "Time taken: $time_taken seconds"
