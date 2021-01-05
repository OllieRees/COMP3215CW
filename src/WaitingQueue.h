/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: WaitingQueue.h is the hashmap structure for tasks waiting for the next deadline
 */ 

/* TODO: Use uthash */

#ifndef TASK_H
#define TASK_H
#include "Task.h"
#endif
#include <stdint.h>
#include <math.h>
#include <string.h>

/* WaitingQueueElement is the element of the waiting queue containing a list of tasks, a key and the number of tasks in the element
 * PARAM: deadline is the deadline of the tasks in the element
 * PARAM: tasks is the list of tasks in the element  
 * PARAM: taskCount is the size of the tasks list
 * PARAM: makes the structure hashable
 */ 
typedef struct WaitingQueueElement {
    int deadline;
    Task ** tasks;
    uint8_t taskCount;
} WaitingQueueElement;


/* WaitingQueue is the list of waiting queue elements 
 * PARAM: queueSize is the number of elements currently in the queue
 * PARAM: elements is the list of elements in the queue
 */ 
typedef struct WaitingQueue {
    uint8_t queueSize;
    WaitingQueueElement ** elements;
} WaitingQueue;

/* DESCR: Constructs a waiting queue with a given size
 * PARAM: tableSize is the size of the waiting queue.
 * RETURN: a pointer to the waiting queue
 */ 
WaitingQueue * createWaitingQueue(uint8_t tableSize);

/* DESCR: Constructs a waiting queue with a given size
 * PARAM: tasks is the initial tasks in the waiting queue
 * PARAM: tableSize is the size of the waiting queue.
 * RETURN: a pointer to the waiting queue
 */ 
WaitingQueue * createFilledWaitingQueue(Task ** tasks, uint8_t tableSize);


/* DESCR: Encodes the deadline into a key for a waiting queue
 * PARAM: the deadline to be encoded
 * PARAM: tableSize is the size of the waiting queue.
 * RETURN: the key associated with the deadline
 */
uint8_t encodeKey(int deadline, uint8_t tableSize); 

/* DESCR: Gets the key based on the deadline of a task
 * PARAM: deadline is the deadline used to encode the key 
 * PARAM: wq is the waiting queue that is associted with the key
 * RETURN: the waiting queue's key associated with the deadline
 */ 
uint8_t getKey(int deadline, WaitingQueue * wq); 

/* DESCR: Pushes a task onto the waiting queue, creating a new element if necessary 
 * PARAM: task is the task being pushed onto the waiting queue
 * PARAM: deadline is the deadline of the task being pushed onto the waiting queue
 * PARAM: wq is the waiting queue having a task pushed onto it
 * RETURN: 1 if the task was successfully pushed, and 0 if it already exists on the queue
 */
int8_t pushWQ(Task * task, int deadline, WaitingQueue * wq);

/* DESCR: pops a task from the waiting queue
 * PARAM: task is the task to be removed from the waiting queue
 * PARAM: deadline is the deadline of the task used to find its key
 * PARAM: wq is the waiting queue holding the task
 * RETURN: the task that was popped, or NULL if it couldn't be found
 */ 
Task * popWQ(Task * task, int deadline, WaitingQueue * wq);

/* DESCR: Pops all the tasks from the index associated with a deadline
 * PARAM: deadline is the index
 * PARAM: wq is the waiting index with the tasks that are to be popped
 * RETURN: the list of the tasks in wq associated with the deadline; NULL if there are no tasks in that deadline.
 */
Task ** popAllWQ(int deadline, WaitingQueue * wq);

/* DESCR: Peeks all the tasks from the index associated with a deadline
 * PARAM: deadline is the index
 * PARAM: wq is the waiting index with the tasks that are to be popped
 * RETURN: the list of the tasks in wq associated with the deadline; NULL if there are no tasks in that deadline.
 */
Task ** peekWQ(int deadline, WaitingQueue * wq); 

/* DESCR: Frees a waiting queue from memory
 * PARAM: The waiting queue to be freed from memory
 * RETURN: 1 if the waiting queue was freed, 0 if it wasn't.
 */
int8_t destroyWaitingQueue(WaitingQueue * wq);
