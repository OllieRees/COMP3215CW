/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: WaitingQueue.h is the hashmap structure for tasks waiting for the next deadline
 */ 

#include "Task.h"
#include <stdint.h>
#include <math.h>
#include <string.h>

/* WaitingQueueElement is the element of the waiting queue containing a list of tasks, a key and the number of tasks in the element
 * PARAM: deadline is the deadline of the tasks in the element
 * PARAM: tasks is the list of tasks in the element  
 * PARAM: taskCount is the size of the tasks list
 */ 
typedef struct WaitingQueueElement {
    uint8_t deadline;
    Task ** tasks;
    uint8_t taskCount;
} WaitingQueueElement;

typedef struct {
    uint8_t queueSize;
    WaitingQueueElement ** elements;
} WaitingQueue;

/* DESCR: Constructs a waiting queue with a given size
 * PARAM: tableSize is the size of the waiting queue.
 * RETURN: a pointer to the waiting queue
 */ 
WaitingQueue * constructWaitingQueue(uint8_t tableSize);

/* DESCR: Encodes the deadline into a key for a waiting queue
 * PARAM: the deadline to be encoded
 * PARAM: tableSize is the size of the waiting queue.
 * RETURN: the key associated with the deadline
 */
uint8_t encodeKey(uint8_t deadline, uint8_t tableSize); 

/* DESCR: Gets the key based on the deadline of a task
 * PARAM: deadline is the deadline used to encode the key 
 * PARAM: wq is the waiting queue that is associted with the key
 * RETURN: the waiting queue's key associated with the deadline
 */ 
uint8_t getKey(uint8_t deadline, WaitingQueue * wq); 

/* DESCR: Pushes a task onto the waiting queue, creating a new element if necessary 
 * PARAM: task is the task being pushed onto the waiting queue
 * PARAM: deadline is the deadline of the task being pushed onto the waiting queue
 * PARAM: wq is the waiting queue having a task pushed onto it
 * RETURN: 1 if the task was successfully pushed, and 0 if it already exists on the queue
 */
int8_t push(Task * task, uint8_t deadline, WaitingQueue * wq);

/* DESCR: Pops all the tasks from the index associated with a deadline
 * PARAM: deadline is the index
 * PARAM: wq is the waiting index with the tasks that are to be popped
 * RETURN: the list of the tasks in wq associated with the deadline; NULL if there are no tasks in that deadline.
 */
Task ** popAll(uint8_t deadline, WaitingQueue * wq);

/* DESCR: Frees a waiting queue from memory
 * PARAM: The waiting queue to be freed from memory
 * RETURN: 1 if the waiting queue was freed, 0 if it wasn't.
 */
int8_t destroyWaitingQueue(WaitingQueue * wq);
