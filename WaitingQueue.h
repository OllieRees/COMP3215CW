/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: WaitingQueue.h is the hashmap structure for tasks waiting for the next deadline
 */ 

#include "Task.h"


typedef struct WaitingQueueElement {
    uint8_t deadline_key;
    Task ** Tasks;
} WaitingQueueElement;

typedef WaitingQueueElement * WaitingQueue; 

/* DESCR: Encodes the deadline into a key for a waiting queue
 * PARAM: the deadline to be encoded
 * RETURN: the key associated with the deadline
 */
uint8_t encodeKey(uint8_t deadline); 

/* DESCR: Decodes a waiting queue's key
 * PARAM: the key to be decoded
 * RETURN: the deadline associated with the key  
 */
uint8_t decodeKey(uint8_t deadline_key); 

/* DESCR: Pushes a task onto the waiting queue, creating a new element if necessary 
 * PARAM: task is the task being pushed onto the waiting queue
 * PARAM: wq is the waiting queue having a task pushed onto it
 * RETURN: 1 if the task was successfully pushed, and 0 if it already exists on the queue
 */
int8_t push(Task * task, WaitingQueue * wq);

/* DESCR: Pops all the tasks from the index associated with a deadline
 * PARAM: deadline is the index
 * PARAM: wq is the waiting index with the tasks that are to be popped
 * RETURN: the list of the tasks in wq associated with the deadline; NULL if there are no tasks in that deadline.
 */
Task ** popAll(uint8_t deadline, WaitingQueue * wq);
