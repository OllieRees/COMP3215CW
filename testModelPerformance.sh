#!/bin/bash

# Use testcase 3: 3 tasks

# from 10 seconds to 1 million in 10 interval gaps

for t in {100..100000..100} 
do
    for a in {1..3}
    do
        echo $t >> performance.txt
        time (./Scheduler ./testCases/test3.txt /dev/null $t $1 > /dev/null) &>> performance.txt
        echo >> performance.txt
    done 
done
