/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Task.h is the interface for the constructor and destructor for the task structure, which represents an executable task.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Task represents an executable task that a schedule has to schedule for execution
 * A Task's name is it's readable indentifier
 * A Task's execution time is the time (in 10 ms) it takes to execute the task
 * A Task's period is the slot in 10 ms that the task can run in before it needs to repeat.
 * A Task's progress is how long it has run for in 10 ms
 */ 
typedef struct Task {
    char * name;
    uint8_t exec_time;
    uint8_t period;
    uint8_t progress;
} Task;

/* DESCR: Creates a new task with a name, execution time and period 
 * PARAM: name is the the name of the new task
 * PARAM: exec_time is the execution time of the new task
 * PARAM: period is the period of the new task
 * RETURN: a pointer to the newly created task
 */
Task * createTask(char * name, uint8_t exec_time, uint8_t period); 

/* DESCR: Updates progress after being interrupted
 * PARAM: task is the task which is having its progress updated
 * PARAM: startTime is the time (in 10 ms) when the task started after being popped from the priority queue
 * PARAM: currentTime is the current time of the scheduler
 */
void updateProgress(Task * task, int startTime, int currentTime);

/* DECSR: Prints the task's details. Used for debugging.
 * PARAM: task is the task being printed.
 */ 
void printTask(Task * task);

/* DESCR: Frees a task from memory
 * PARAM: task is the task to be freed from memory
 */
void destroyTask(Task * task);
