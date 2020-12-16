/* Author: Ollie Rees
 * Project: COMP3215 Coursework
 * File: TaskPriorityQueue.h controls the interface for a priority queue holding tasks
 */ 

#include "Task.h"

/* TaskPriorityQueue is a heap structure with the element holding a priority and a task
 * PARAM: priority is the priority of the element  
 * PARAM: task is the task of the element
 * PARAM: leftBranch is the left branch of the heap (NULL means there is no left branch)
 * PARAM: rightBranch is the right branch of the heap (NULL means there is no right branch)
 */ 
typedef struct TaskPriorityQueue {
    uint8_t priority;
    Task * task;
    struct TaskPriorityQueue * leftBranch;
    struct TaskPriorityQueue * rightBranch;
} TaskPriorityQueue;

/* DESCR: Insert a new task into the priority queue 
 * PARAM: task is the new task
 * PARAM: priority is the priority of the new task
 * PARAM: tpq is the the priority queue that task is being inserted into
 * RETURN: 1 if it was successfully inserted, 0 if it already exists in the priority queue.
 */ 
int8_t insert(Task * task, uint8_t priority, TaskPriorityQueue * tpq);

/* DESCR: Remove a task from the priority queue.
 * PARAM: name is the name of the task to be removed
 * PARAM: tpq is the priority queue where the task is being removed.
 * RETURN: 1 if it was successfully removed, 0 if it could not be found.
 */ 
int8_t remove(char * name, TaskPriorityQueue * tpq);

/* DESCR: Finds the task in the priority queue. 
 * PARAM: name is the name of the task.
 * PARAM: tpq is the priority queue where the task is being searched.
 * RETURN: The task priority queue with the searched task as the root. If the task doesn't exist in the priority queue then it returns NULL.
 */ 
TaskPriorityQueue * search(char * name, TaskPriorityQueue * tpq);

/* DESCR: Changes the priority of a task in the task priority queue 
 * PARAM: task is the task which is having its priority changed.
 * PARAM: newPriority is the new priority value of the task.
 * PARAM: tpq is the task priority queue with the task and old priority.
 * RETURN: The new tpq formed via changing the priority of task.
 */ 
TaskPriorityQueue * changePriority(Task * task, uint8_t newPriority, TaskPriorityQueue * tpq);

/* DESCR: Gets the task with the highest priority.
 * PARAM: tpq is the priority queue which is being searced for the highest priority task.
 * RETURN: the task with the highest priority.
 */ 
Task * getHighestPriorityTask(TaskPriorityQueue * tpq);

/* DESCR: heapifys turns the binary tree into a heap structure 
 * PARAM: tpq is the binary tree, but using the same element type as the task priority queue
 * RETURN: the new priority queue as a heap
 */ 
TaskPriorityQueue * heapify(TaskPriorityQueue * tpq);
