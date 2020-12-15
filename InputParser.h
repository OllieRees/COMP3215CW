/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework 
 * File: InputParser.h is the interface for reading the input file and creating Tasks from that information. 
 */ 

#include "Task.h"
#include <stdio.h>

/* DESCR: Parses the line detailing how many tasks there are to parse
 * PARAM: taskCountLine is the line with the number of tasks to be parsed 
 * STR_FORMAT: NumTasks [taskCount]
 * RETURN: the number of tasks that need to be parsed
 */ 
int parseTaskCountLine(char * taskCountLine);

/* DESCR: Parses the line giving information about a task
 * PARAM: taskLine is is the line with the information about a task 
 * STR_FORMAT: The line's format is [taskname] [exec_time] [period]
 * RETURN: a new task based on the information given in the line 
 */ 
Task * parseTaskLine(char * taskLine);
