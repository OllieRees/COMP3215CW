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
    wq -> elements = (WaitingQueueElement *) malloc(sizeof(WaitingQueueElement) * tableSize);
    
    //set elements
    uint8_t i;
    for(i = 0; i < tableSize; i++) {
        wq -> elements[i].deadline = 0;
        wq -> elements[i].taskCount = 0;
        wq -> elements[i].tasks = NULL;
    }
    return wq;
}

WaitingQueue * createFilledWaitingQueue(Task ** tasks, uint8_t taskCount, uint8_t tableSize) {
    WaitingQueue * wq = createWaitingQueue(tableSize);
    
    //add elements
    uint8_t i;
    for(i = 0; i < taskCount; i++) {
        pushWQ(tasks[i], tasks[i] -> period, wq);
    }
    return wq;
}

uint8_t getKey(int deadline, WaitingQueue * wq) {
    //knuth's multiplicative method using (sqrt(5) - 1)/2 as the constant
    double const A = 0.61803398875; 
    uint8_t key = floor(wq->queueSize * (deadline * A - floor(deadline * A)));
    
    //linear probing 
    uint8_t i, k;
    for(k = key, i = 0; i < wq -> queueSize; k = (k + 1) % wq->queueSize, i++) {
        if(wq -> elements[k].taskCount == 0)
            return k;
    }
    
    //couldn't find empty spot
    //printf("Error: Hash Table is full\n");
    return wq -> queueSize + 1;
}

uint8_t findKey(int deadline, WaitingQueue * wq) {
    //knuth's multiplicative method using (sqrt(5) - 1)/2 as the constant
    double const A = 0.61803398875; 
    uint8_t key = floor(wq->queueSize * (deadline * A - floor(deadline * A)));

    //linear probing
    uint8_t i, k;
    for(k = key, i = 0; i < wq -> queueSize; k = (k + 1) % wq->queueSize, i++) {
        if(wq -> elements[k].deadline == deadline) 
            return k;
    }

    //couldn't find empty spot
    return wq -> queueSize + 1;
}

int8_t pushWQ(Task * task, int deadline, WaitingQueue * wq) {
    uint8_t key = findKey(deadline, wq);
    if(key == wq -> queueSize + 1) { //element with deadline doesn't exist yet
        key = getKey(deadline, wq);
        if(key == wq -> queueSize + 1) //doesn't have an empty spot 
            return 0;
    } else {
        printf("Checking task %s doesn't exist in the map\n", task -> name);
        //check if task already exists in wq[key]
        uint8_t i; 
        for(i = 0; i < wq -> elements[key].taskCount; i++) {
            if(strcmp(wq -> elements[key].tasks[i] -> name, task -> name) == 0)
                return 0;
        }    
    }
    printf("Push %s to %d\n", task -> name, key); 
    
    //if empty assign a deadline and allocate memory for task
    if (wq -> elements[key].taskCount == 0) {
        wq -> elements[key].deadline = deadline; 
        wq -> elements[key].tasks = (Task **) malloc(sizeof(Task *));
    }

    //add task to the end of the element 
    wq -> elements[key].tasks = realloc(wq -> elements[key].tasks, sizeof(Task *) * (wq -> elements[key].taskCount + 1));
    wq -> elements[key].tasks[wq -> elements[key].taskCount] = task;
    wq -> elements[key].taskCount++;
    return 1;
}

Task ** popAllWQ(int deadline, WaitingQueue * wq) {
    //find key with deadline
    uint8_t key = findKey(deadline, wq);
    
    //check if it exists
    if(key == wq -> queueSize + 1) 
        return NULL;

    printf("Pop tasks in wq at %d\n", key); 

    //save task list
    Task ** tasks = wq -> elements[key].tasks;
    
    //reset the element's params
    wq -> elements[key].tasks = NULL;
    wq -> elements[key].taskCount = 0;
    wq -> elements[key].deadline = 0;

    return tasks;
}

Task ** peekWQ(int deadline, WaitingQueue * wq) {
    uint8_t key = findKey(deadline, wq);
    if(key == wq -> queueSize + 1)
        return NULL;
    return wq -> elements[key].tasks;
}

void printWaitingQueue(WaitingQueue* wq) {    
    for(int i = 0; i < wq -> queueSize; i++) {
        printf("{");
        for(int j = 0; j < wq -> elements[i].taskCount; j++) {
            printTask(wq -> elements[i].tasks[j]);
        }
        printf("}\n");
    }
}

int8_t destroyWaitingQueue(WaitingQueue *wq) {
    //free elements
    free(wq -> elements);
    free(wq);
    return 1;
}
