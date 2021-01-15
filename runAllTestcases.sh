#!/bin/bash

./Scheduler ./testCases/test1.txt output1_RMS.txt 1000 0
./Scheduler ./testCases/test1.txt output1_EDF.txt 1000 1
./Scheduler ./testCases/test2.txt output2_RMS.txt 1000 0
./Scheduler ./testCases/test2.txt output2_EDF.txt 1000 1
./Scheduler ./testCases/test3.txt output3_RMS.txt 1000 0
./Scheduler ./testCases/test3.txt output3_EDF.txt 1000 1
./Scheduler ./testCases/test4.txt output4_RMS.txt 1000 0
./Scheduler ./testCases/test4.txt output4_EDF.txt 1000 1
