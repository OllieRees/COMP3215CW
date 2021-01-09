/* Author: Ollie Rees (or1g18) 
 * Project: COMP3215 Coursework
 * File: HashMap.c is the implementation of the hashmap
 * Previously it was WaitingQueue.c
 */ 

#include "HashMap.h"
#include <stdio.h>

WaitingQueue * createWaitingQueue(uint8_t tableSize) {
    WaitingQueue * wq = (WaitingQueue *) malloc(sizeof(WaitingQueue));
    wq -> queueSize = tableSize;
    wq -> elements = (WaitingQueueElement **) malloc(sizeof(WaitingQueueElement *) * tableSize);
    
    //set elements
    uint8_t i;
    for(i = 0; i < tableSize; i++) {
        wq -> elements[i] = (WaitingQueueElement *) malloc(sizeof(WaitingQueueElement));
        wq -> elements[i] -> deadline = 0;
        wq -> elements[i] -> taskCount = 0;
        wq -> elements[i] -> tasks = NULL;
    }
    return wq;
}

WaitingQueue * createFilledWaitingQueue(Task ** tasks, uint8_t tableSize) {
    WaitingQueue * wq = (WaitingQueue *) malloc(sizeof(WaitingQueue));
    wq -> queueSize = tableSize;
    wq -> elements = (WaitingQueueElement **) malloc(sizeof(WaitingQueueElement *) * tableSize);
    //add elements
    uint8_t i;
    for(i = 0; i < tableSize; i++) {
        pushWQ(tasks[i], tasks[i] -> period, wq);
    }
    return wq;
}

uint8_t getKey(int deadline, WaitingQueue * wq) {
    //knuth's multiplicative method using (sqrt(5) - 1)/2 as the constant
    double const A = 0.61803398875; 
    uint8_t key = floor(wq->queueSize * (deadline * A - floor(deadline * A)));
    
    //linear probing - find first element that is null or part of the deadline
    //all fine until key = 0, stop when key = wq -> queueSize - 1
    uint8_t i;
    uint8_t lastI = key > 0 ? key - 1 : wq -> queueSize - 1;
    for(i = key; i != lastI; i = (i + 1) % wq->queueSize) {
        if(wq -> elements[key] -> deadline == deadline || wq -> elements[key] -> taskCount == 0)
            break;
    }
    
    //couldn't find empty spot
    if(i == lastI) {
        printf("Error: Hash Table is full\n");
        return wq -> queueSize + 1;
    }

    return i;
}

uint8_t findKey(int deadline, WaitingQueue * wq) {
    //knuth's multiplicative method using (sqrt(5) - 1)/2 as the constant
    double const A = 0.61803398875; 
    uint8_t key = floor(wq->queueSize * (deadline * A - floor(deadline * A)));

    //linear probing - find first element that is null or part of the deadline
    //all fine until key = 0, stop when key = wq -> queueSize - 1
    uint8_t i;
    uint8_t lastI = key > 0 ? key - 1 : wq -> queueSize - 1;
    for(i = key; i != lastI; i = (i + 1) % wq->queueSize) {
        if(wq -> elements[key] -> deadline == deadline)
            break;
    }

    //couldn't find empty spot
    if(i == lastI) {
        printf("Error: Element with %d doesn't exist in table\n", deadline);
        return wq -> queueSize + 1;
    }

    return i;
}

int8_t pushWQ(Task * task, int deadline, WaitingQueue * wq) {
    uint8_t key = findKey(deadline, wq);
    if(key == wq -> queueSize + 1) { //element with deadline doesn't exist yet
        key = getKey(deadline, wq);
        if(key == wq -> queueSize + 1) //doesn't have an empty spot 
            return 0;
    } else {
        //check if task already exists in wq[key]
        uint8_t i; 
        for(i = 0; i < wq -> elements[key] -> taskCount; i++) {
            if(strcmp(wq -> elements[key] -> tasks[i] -> name, task -> name) == 0)
                return 0;
        }    
    }
    
    WaitingQueueElement * element = wq -> elements[key];
    
    //if empty assign a deadline and allocate memory for task
    if (element -> taskCount == 0) {
        element -> deadline = deadline; 
        element -> tasks = (Task **) malloc(sizeof(Task));
    }

    //add task 
    (element -> taskCount)++;
    element -> tasks = realloc(element -> tasks, sizeof(Task) * element -> taskCount);
    element -> tasks[element -> taskCount - 1] = task;
    return 1;
}

Task ** popAllWQ(int deadline, WaitingQueue * wq) {
    //find key with deadline
    uint8_t key = findKey(deadline, wq);
    
    //check if it exists
    if(key == wq -> queueSize + 1) 
        return NULL;

    //save task list
    Task ** tasks = wq -> elements[key] -> tasks;
    
    //reset the element's params
    wq -> elements[key] -> tasks = NULL;
    wq -> elements[key] -> taskCount = 0;
    wq -> elements[key] -> deadline = 0;

    return tasks;
}

Task ** peekWQ(int deadline, WaitingQueue * wq) {
    uint8_t key = findKey(deadline, wq);
    if(key == wq -> queueSize + 1)
        return NULL;
    return wq -> elements[key] -> tasks;
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
