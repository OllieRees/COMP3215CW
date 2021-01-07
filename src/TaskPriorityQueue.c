#include "TaskPriorityQueue.h"

/* DESCR: Get's the parent node given the index of a child node in the queue 
 * PARAM: nodeIndex is the child node's index 
 * PARAM: tpq is the the priority queue with the child and parent node
 * RETURN: The priority queue element that is the parent node.
 */ 
Task * getParentNode(uint8_t nodeIndex, TaskPriorityQueue * tpq) {
    return tpq -> tasks[(nodeIndex - 1)/2];
}

/* DESCR: Quickly sorts a list of tasks in O(nlog(n)) time. It uses scheduling algorithm to check the priorities of the tasks.
 * PARAM: tasks is the list of the tasks being sorted.
 * PARAM: taskCount is the number of tasks in the list.
 * PARAM: priorityAlg is the scheduling algorithm used to determine the prioroity of each task.
 * PARAM: time is used in the priority algorithm for EDF
 * SOURCE: https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
 */ 
void quicksort(Task ** tasks, uint8_t taskCount, SchedulingAlgorithm priorityAlg, int time) {
    //base case
    if (taskCount < 2) 
        return;
    int pivot = priorityAlg(tasks[taskCount / 2], time);
 
    int i, j;
    for (i = 0, j = taskCount - 1; ; i++, j--) {
        //skip the tasks in the right place
        while (priorityAlg(tasks[i], time) < pivot) 
            i++;
        while (priorityAlg(tasks[j], time) > pivot) 
            j--;
      
        //if we've passed to the other side or on the pivot index
        if (i >= j) 
            break;

        Task * temp = tasks[i];
        tasks[i]    = tasks[j];
        tasks[j]    = temp;
  }
 
  quicksort(tasks, i, priorityAlg, time);
  quicksort(tasks + i, taskCount - i, priorityAlg, time);
}

TaskPriorityQueue * createTaskPriorityQueue(Task ** tasks, uint8_t taskCount) {
    TaskPriorityQueue * tpq = malloc(sizeof(TaskPriorityQueue));
    tpq -> tasks = malloc(sizeof(Task) * taskCount);
    tpq -> tasks = tasks;
    tpq -> taskCount = taskCount;
    heapify(tpq, assignPriority_RMS, 0);
    return tpq;
}

int8_t insertTPQ(Task * task, TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time) {
    //insert element to the end of the priority queue 
    uint8_t i = tpq -> taskCount - 1;
    tpq -> tasks[i] = task;
    tpq -> taskCount++;
    heapify(tpq, priorityAlg, time);
    return tpq -> taskCount != i;
}

int8_t removeTPQ(char * name,  TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time) {
    //get index of the node to be removed
    int removedNodeIndex = searchIndexTPQ(name, tpq);
    
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

    heapify(tpq, priorityAlg, time);
    return 1;
}


Task * popAndAddTPQ(Task * task, TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time) {
    Task * highestPTask = tpq -> tasks[0];
    
    //put last node at root and new task in the last spot
    if(tpq -> taskCount > 1) {
        tpq -> tasks[0] = tpq -> tasks[tpq -> taskCount - 1];
        tpq -> tasks[tpq -> taskCount - 1] = task;
    }

    heapify(tpq, priorityAlg, time);
    return highestPTask;

}

Task * searchElementTPQ(char * name, TaskPriorityQueue * tpq) {
    for(int i = 0; i < tpq -> taskCount; i++) {
        if(strcmp(tpq -> tasks[i] -> name, name) == 0)
            return tpq -> tasks[i];
    }
    return NULL;
}

uint8_t searchIndexTPQ(char * name, TaskPriorityQueue * tpq) {
    for(int i = 0; i < tpq -> taskCount; i++) {
        if(strcmp(tpq -> tasks[i] -> name, name) == 0)
            return i;
    }
    return -1;
}

Task * getHighestPriorityTask(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time) {
    Task * highestPTask = tpq -> tasks[0];
    removeTPQ(highestPTask -> name, tpq, priorityAlg, time);
    return highestPTask;
}

Task * peekHighestPriorityTask(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time) {
    return tpq -> tasks[0];
}

void heapify(TaskPriorityQueue * tpq, SchedulingAlgorithm priorityAlg, int time) {
    quicksort(tpq -> tasks, tpq -> taskCount, priorityAlg, time); 
}

int8_t destroyTaskPriorityQueue(TaskPriorityQueue * tpq) {
    free(tpq);
    return 1;
}
