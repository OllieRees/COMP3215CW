/* Author: Ollie Rees (or1g18) 
 * Project: COMP3215 Coursework
 * File: WaitingQueue.c is the implementation of waiting queue 
 */ 

#include "WaitingQueue.h"

WaitingQueue * constructWaitingQueue(uint8_t tableSize) {
    //If tableSize is a power of 2, add 1 more to tableSize
    if((tableSize & (tableSize - 1)) == 0) 
        tableSize++;
    WaitingQueue * wq = malloc(sizeof(WaitingQueue));
    wq -> elements = malloc(sizeof(WaitingQueueElement) * tableSize);
    wq -> queueSize = tableSize;
    return wq;
}

uint8_t encodeKey(uint8_t deadline, uint8_t tableSize) {
    //multiplicative method using (sqrt(5) - 1)/2 as the constant
    double const A = 0.61803398875; 
    return floor(tableSize * (deadline * A - floor(deadline * A)));
}

uint8_t getKey(uint8_t deadline, WaitingQueue * wq) {
    uint8_t key = encodeKey(deadline, wq -> queueSize);
    //probing
    while(wq -> elements[key] -> deadline != deadline || wq -> elements[key] -> taskCount != 0) {
        key++;
    }
    return key;
}

int8_t push(Task * task, uint8_t deadline, WaitingQueue * wq) {
    //get key
    uint8_t key = getKey(deadline, wq);
        
    WaitingQueueElement * element = wq -> elements[key];

    //check if task is in wq[key]
    uint8_t i; 
    for(i = 0; i < element -> taskCount; i++) {
        if(strcmp(element -> tasks[i] -> name, task -> name))
            return 0;
    }
    
    //add task 
    (element -> taskCount)++;
    element = realloc(element -> tasks, sizeof(Task) * element -> taskCount);
    element -> tasks[element -> taskCount] = task;
    return 1;
}

Task ** popAll(uint8_t deadline, WaitingQueue * wq) {
    uint8_t key = getKey(deadline, wq);
    
    //save task list
    Task ** tasks = wq -> elements[key] -> tasks;
    
    //reset the element's params
    wq -> elements[key] -> tasks = NULL;
    wq -> elements[key] -> taskCount = 0;
    wq -> elements[key] -> deadline=0;

    return tasks;
}

int8_t destroyWaitingQueue(WaitingQueue *wq) {
   //free elements
   uint8_t i;
   for(i = 0; i < wq -> queueSize; i++) {
        free(wq -> elements[i]);
   }
   free(wq);
   return 1;
}
