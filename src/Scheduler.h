/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Scheduler.h contains information about the scheduler data structure, and manipulations of the data within the struct.
 */

#ifndef TASK_H
#define TASK_H
#include "Task.h"
#endif
#include "TaskPriorityQueue.h"
#include "HashMap.h"
#include "EDF.h"
#include "RMS.h"
#include "OutputParser.h"
#include <string.h>
#include <stdio.h> 

typedef struct Scheduler {
    Task ** tasks;
    uint8_t taskCount;
    TaskPriorityQueue * taskPriorityQueue;
    WaitingQueue * waitingQueue;
} Scheduler;


/* DESCER: Create a new scheduler with the given task and priorty queue.
 * PARAM: tasks are the list of the tasks the scheduler has; can be NULL.
 * RETURN: a pointer to the newly created scheduler
 */ 
Scheduler * createScheduler(Task ** tasks, const uint8_t taskCount);

/* DESCR: Runs a scheduler for a time
 * PARAM: supertime is the time the scheduler is run for
 * PARAM: fileLoc is the location of the output file
 * PARAM: priorityFunc is the priority function used to prioritise tasks during the supertime period.
 * PARAM: schedule is the scheduler being run 
 */ 
void runScheduler(int supertime, char * fileLoc, SchedulingAlgorithm * priorityFunc, Scheduler * schedule);

/* DESCR: Frees a scheduler, and its tasks and priority queue from memory 
 * PARAM: schedule is the scheduler being freed 
 * RETURN: 1 if the schedule could be freed.
 */ 
int8_t freeScheduler(Scheduler * schedule);
