/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: OutputParser.h contains functions for passing a message to the output file
 */

#ifndef TASK_H
#define TASK_H
#include "Task.h"
#endif
#include <stdio.h>

/* void parseMessage(char * message, Task * task, int time, FILE * outputFile); instead? */

/* DESCR: Creates a new output file 
 * PARAM: location and name of the output file
 * RETURN: The file pointer with the mode set to write
 */
FILE * createOutputFile(char * fileLoc);

/* DESCR: Parses a message to an output file detailing that a task has begun execution 
 * PARAM: task is the task that has been successfully executed
 * PARAM: time is the time the task was executed
 * PARAM: outputFile is the output file the message is being parsed to
 */ 
void parseExecution(Task * task, int time, FILE * outputFile);

/* DESCR: Parses a message to an output file detailing that a task has missed
 * PARAM: task is the task that has missed its deadline
 * PARAM: time is the time the deadline the task missed
 * PARAM: outputFile is the output file the message is being parsed to
 */ 
void parseMiss(Task * task, int time, FILE * outputFile);

/* DESCR: Parses a message to an output file detailing that a task has completed 
 * PARAM: task is the task that has been successfully complete 
 * PARAM: time is the time the task was completed
 * PARAM: outputFile is the output file the message is being parsed to
 */ 
void parseCompletion(Task * task, int time, FILE * outputFile);

/* DESCR: Closes the output file with a message at the end of the file
 * PARAM: the file being closed
 */
void closeOutputFile(FILE * file);
