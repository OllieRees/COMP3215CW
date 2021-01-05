/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Scheduler.h contains information about the scheduler data structure, and manipulations of the data within the struct.
 */

#ifndef TASK_H
#define TASK_H
#include "Task.h"
#endif
#include "TaskPriorityQueue.h"
#include "WaitingQueue.h"
#include "SchedulingAlgorithms/EDF.c"
#include "SchedulingAlgorithms/RMS.c"
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
Scheduler * createScheduler(Task ** tasks, uint8_t taskCount);

/* DESCR: Finds a task in the scheduler
 * PARAM: name is the name of the task to be found
 * PARAM: schedule is the schedule being searched
 * RETURN: The task or NULL if the task doesn't exist 
 */ 
Task * findTask(char * name, Scheduler * schedule);

/* DESCR: Runs a scheduler for a time
 * PARAM: supertime is the time the scheduler is run for
 * PARAM: schedule is the scheduler being run 
 */ 
void runScheduler(int supertime, Scheduler * schedule);

/* DESCR: Frees a scheduler, and its tasks and priority queue from memory 
 * PARAM: schedule is the scheduler being freed 
 * RETURN: 1 if the schedule could be freed.
 */ 
int8_t freeScheduler(Scheduler * schedule);
