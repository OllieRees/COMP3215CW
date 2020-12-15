/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Task.h is the interface for the constructor and destructor for the task structure, which represents an executable task.
 */

#include <stdlib.h>
#include <stdint.h>

/* Task represents an executable task that a schedule has to schedule for execution
 * A Task's name is it's readable indentifier
 * A Task's execution time is the time (in 10 ms) it takes to execute the task
 * A Task's period is the slot in 10 ms that the task can run in before it needs to repeat. 
 */ 
typedef struct Task {
    char * name;
    uint8_t exec_time;
    uint8_t period;
} Task;

/* DESCR: Creates a new task with a name, execution time and period 
 * PARAM: name is the the name of the new task
 * PARAM: exec_time is the execution time of the new task
 * PARAM: period is the period of the new task
 * RETURN: a pointer to the newly created task
 */
Task * createTask(char * name, uint8_t exec_time, uint8_t period);

/* DESCR: Frees a task from memory
 * PARAM: task is the task to be freed from memory
 * RETURN: 1 if the task was successfully freed; 0 if the task can't be freed, due to the task depending on another structure. 
 */
int destroyTask(Task * task);
