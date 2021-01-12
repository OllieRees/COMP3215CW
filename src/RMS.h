#ifndef TASK_H
#define TASK_H
#include "Task.h"
#endif

/* DESCR: Assigns priority of a task using RMS; RMS' priority is based off the task's period
 * PARAM: task is the task which is getting its priority assigned
 * PARAM: time is the current time that the function is called
 * RETURN: the priority of the task
 */ 
uint8_t assignPriority_RMS(Task * task, int time);

