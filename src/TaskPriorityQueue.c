#include "TaskPriorityQueue.h"

/* DESCR: Get's the parent node given the index of a child node in the queue 
 * PARAM: nodeIndex is the child node's index 
 * PARAM: tpq is the the priority queue with the child and parent node
 * RETURN: The priority queue element that is the parent node.
 */ 
Task * getParentNode(uint8_t nodeIndex, TaskPriorityQueue * tpq) {
    return tpq -> tasks[(nodeIndex - 1)/2];
}

/* DESCR: Quickly sorts a list of tasks in O(log(n)) time based on the priorityAlg's output
 * PARAM: tasks is the list of tasks
 * PARAM: task count is the number of tasks in tasks.
 * PARAM: priorityAlg is the algorithm that decies the priority for a task
 * CREDIT: rosettacode.com/wiki/Sorting_algorithms/Quicksort#C
 */ 
void quicksort(Task ** tasks, uint8_t taskCount, SchedulingAlgorithm priorityAlg) {
    //base case for recursion
    if (taskCount < 2) 
        return;
 
    int pivot = priorityAlg(tasks[taskCount / 2]);
 
    int i, j;
    for (i = 0, j = taskCount - 1; ; i++, j--) {
        //if the tasks are on the right side of the pivot, leave it
        while (priorityAlg(tasks[i]) < pivot) 
            i++;
        while (priorityAlg(tasks[j]) > pivot) 
            j--;
        
        //conditional for breaking 
        if (i >= j) 
            break;
 
        //swap the two that belong on the wrong side
        Task * temp     = tasks[i];
        tasks[i]        = tasks[j];
        tasks[j]        = temp;
    }
    
    //recursive call for the two sides
    quicksort(tasks, i, priorityAlg);
    quicksort(tasks + i, taskCount - i, priorityAlg);
} 

TaskPriorityQueue * createTaskPriorityQueue(Task ** tasks, uint8_t taskCount, SchedulingAlgorithm priorityAlg) {
    //lower period -> higher priority
    //allocate memory for the priority queue and set taskcount
    TaskPriorityQueue * tpq = malloc(sizeof(TaskPriorityQueue));
    tpq -> tasks = malloc(sizeof(Task) * taskCount);
    tpq -> tasks = tasks;
    tpq -> taskCount = taskCount;
    tpq = heapify(tpq, priorityAlg);
    return tpq;
}

int8_t insert(Task * task, TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg) {
    //insert element to the end of the priority queue 
    uint8_t i = tpq -> taskCount - 1;
    tpq -> tasks[i] = task;
    tpq -> taskCount++;
    tpq = heapify(tpq, priorityAlg);
    return tpq -> taskCount != i;
}

int8_t remove(char * name,  TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg) {
    //get index of the node to be removed
    int removedNodeIndex = searchIndex(name, tpq);
    
    //task doesn't exist in the p. queue
    if(removedNodeIndex == -1)
        return 0;

    //put last node in the position of the removedNode
    if(removedNodeIndex != tpq -> taskCount - 1) {
        tpq -> tasks[removedNodeIndex] = tpq -> tasks[tpq -> taskCount - 1];
        tpq -> tasks[tpq -> taskCount - 1] = NULL;
    }

    //reduce task count
    tpq -> taskCount--;

    tpq = heapify(tpq, priorityAlg);
    return 1;
}

Task * searchElement(char * name, TaskPriorityQueue * tpq) {
    for(int i = 0; i < tpq -> taskCount; i++) {
        if(strcmp(tpq -> tasks[i] -> name, name) == 0)
            return tpq -> tasks[i];
    }
    return NULL;
}

uint8_t searchIndex(char * name, TaskPriorityQueue * tpq) {
    for(int i = 0; i < tpq -> taskCount; i++) {
        if(strcmp(tpq -> tasks[i] -> name, name) == 0)
            return i;
    }
    return -1;
}

Task * getHighestPriorityTask(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg) {
    Task * highestPTask = tpq -> tasks[0];
    remove(highestPTask -> name, tpq, priorityAlg);
    return highestPTask;
}

TaskPriorityQueue * heapify(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg) {
    quicksort(tpq -> tasks, tpq -> taskCount, priorityAlg);
    return tpq;
}

int8_t destroyTaskPriorityQueue(TaskPriorityQueue * tpq) {
    free(tpq);
}
