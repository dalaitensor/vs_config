#!/bin/bash
# filepath: /Users/mike/development/c++/cp/problems_online/E/run_tests.sh

# Create output directory if it doesn't exist
mkdir -p testcase/output

# Compile the solution
gcc -o solA solA.c

# Loop through all test cases
for testcase in testcase/input/input*.txt; do
    # Get the test case number
    num=$(echo $testcase | grep -o "[0-9]\+")
    
    echo "Running test case $num..."
    
    # Run the program with the test case input and save output to answers directory
    ./solA < $testcase > testcase/output/output$num.txt
done

echo "All test cases processed. Answers saved in the 'answers' directory."