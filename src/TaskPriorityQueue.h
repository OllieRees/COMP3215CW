/* Author: Ollie Rees
 * Project: COMP3215 Coursework
 * File: TaskPriorityQueue.h controls the interface for a priority queue holding tasks
 */ 

#ifndef TASK_H
#define TASK_H
#include "Task.h"
#endif
#include <string.h>
#include <stdint.h>
#include <stdio.h>

/* DESCR: Task Priority Queue is a list of Task Priority Queue Elements 
 * PARAM: tasks is the list of tasks that make up the arrayified priority queue
 * PARAM: taskCount is the number of tasks in the heap.
 * */ 
typedef struct TaskPriorityQueue {
    Task ** tasks;
    uint8_t taskCount;
} TaskPriorityQueue;

/* Functor for assigning priority based on an algorithm like RMS or EDF */ 
typedef uint8_t (SchedulingAlgorithm)(Task *, int);

/* DESCR: Creates a new task priority queue from a list of tasks
 * PARAM: tasks are the list of tasks that fill the priority queue
 * PARAM: taskCount is the number of tasks in the list, tasks.
 * PARAM: priorityAlg is the priority assignment algorithm used to initally heapify the priority queue.
 * RETURN: the task priority queue that is built from tasks
 */ 
TaskPriorityQueue * createTaskPriorityQueue(Task ** tasks, uint8_t taskCount, SchedulingAlgorithm priorityAlg);

/* DESCR: Insert a new task into the priority queue 
 * PARAM: task is the new task
 * PARAM: tpq is the the priority queue that task is being inserted into
 * PARAM: priorityAlg is the function used to update priorities 
 * PARAM: time is the current time when the function is called. Used by the scheduling algorithm.
 * RETURN: 1 if it was successfully inserted, 0 if it already exists in the priority queue.
 */ 
int8_t insertTPQ(Task * task, TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time);

/* DESCR: Remove a task from the priority queue.
 * PARAM: name is the name of the task to be removed.
 * PARAM: tpq is the priority queue where the task is being removed. 
 * PARAM: priorityAlg is the function used to update priorities 
 * PARAM: time is the current time when the function is called. Used by the scheduling algorithm.
 * RETURN: 1 if it was successfully removed, 0 if it could not be found.
 */ 
int8_t removeTPQ(char * name, TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time);

/* DESCR: Pop the root off the task priority queue and add a new task to the queue.
 * PARAM: task is the task being added. 
 * PARAM: tpq is the task priority queue which is having its root popped and a new task being added
 * PARAM: priorityAlg is the algorithm to determine priority of the tasks in the queue
 * PARAM: time is the current time the method was called. Used by the priorityAlg.
 * RETURN: the root of the priority queue.
 */ 
Task * popAndAddTPQ(Task * task, TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time);

/* DESCR: Finds the task in the priority queue. 
 * PARAM: name is the name of the task.
 * PARAM: tpq is the priority queue where the task is being searched.
 * RETURN: The task priority queue with the searched task as the root. If the task doesn't exist in the priority queue then it returns NULL.
 */ 
Task * searchTaskTPQ(char * name, TaskPriorityQueue * tpq);

/* DESCR: Finds the index of a task in the priority queue 
 * PARAM: name is the name of the task being searched for 
 * PARAM: tpq is the the priority queue being searched 
 * RETURN: the index of the task or -1 if the task couldn't be found in the priority queue
 */ 
int16_t searchIndexTPQ(char * name, TaskPriorityQueue * tpq);

/* DESCR: Gets the task with the highest priority, and removes it from the priority queue.
 * PARAM: tpq is the priority queue which is being searced for the highest priority task.
 * PARAM: priorityAlg is the function used to update priorities 
 * PARAM: time is the current time when the function is called. Used by the scheduling algorithm.
 * RETURN: the task with the highest priority.
 */ 
Task * getHighestPriorityTask(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time);

/* DESCR: Gets the task with the highest priority, without removing it from the priority queue.
 * PARAM: tpq is the priority queue which is being searced for the highest priority task.
 * RETURN: the task with the highest priority.
 */ 
Task * peekHighestPriorityTask(TaskPriorityQueue * tpq);

/* DESCR: heapifys turns the binary tree into a heap structure, and updates priorities 
 * PARAM: tpq is the binary tree, but using the same element type as the task priority queue
 * PARAM: priorityAlg is the function used to update priorities 
 * PARAM: time is the current time when the function is called. Used by the scheduling algorithm.
 */ 
void heapify(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time); 

/* DESCR: Prints the task priority queue. Used for debugging.
 * PARAM: tpq is the task priority queue being printed.
 */ 
void printTPQ(TaskPriorityQueue * tpq);

/* DESCR: Frees a task priority queue from memory
 * PARAM: tpq is the priority queue being freed from memory
 * RETURN: 1 if the tpq was sucessfully freed from memory, 0 otherwise.
 */ 
int8_t destroyTaskPriorityQueue(TaskPriorityQueue * tpq);
