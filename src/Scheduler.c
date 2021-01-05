/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Scheduler.c is the implementation of the scheduler structure, assigning the schedulers members and running the scheduler.
 */ 
#include "Scheduler.h"

Scheduler * createScheduler(Task ** tasks, uint8_t taskCount) {
    Scheduler * schedule = malloc(sizeof(Scheduler));
    schedule -> tasks = tasks;
    schedule -> taskCount = taskCount;
    schedule -> taskPriorityQueue = createTaskPriorityQueue(tasks, taskCount, assignPriority_RMS);
    schedule -> waitingQueue = createFilledWaitingQueue(tasks, taskCount); 
    
    //add all tasks to waiting queue
    return schedule;
}

Task * findTask(char * name, Scheduler * schedule) {
    uint8_t i;
    for(i = 0; i < schedule -> taskCount; i++) {
        if(strcmp(schedule -> tasks[i] -> name, name)) 
            return schedule -> tasks[i];
    }
    return NULL;
}

void runScheduler(int supertime, Scheduler * schedule){
    //set up output file
    FILE * outputFile = createOutputFile("./output.txt");  

    //set up current task
    Task * currTask = getHighestPriorityTask(schedule -> taskPriorityQueue, assignPriority_RMS, 0); 
    
    //time loop
    unsigned int startTime = 0; //used to save start time of current task
    unsigned int t;
    for(t = 0; t < supertime; t++) {
        
        //miss
        if(peekWQ(t, schedule -> waitingQueue) != NULL) {
            //for each task
            Task ** tasks = popAllWQ(t, schedule -> waitingQueue);
            uint8_t i;
            for(i = 0; tasks[i] != NULL; i++) {
                //if progress isn't exectime parse miss message 
                if(tasks[i] -> progress == tasks[i] -> exec_time)
                    parseMiss(tasks[i], t, outputFile);
                //reset progress to 0
                tasks[i] -> progress = 0;
                //add task back to the waiting queue with new deadline
                pushWQ(tasks[i], t + tasks[i] -> period, schedule -> waitingQueue);
            }
        }
       
        //interrupt
        if(peekHighestPriorityTask(schedule -> taskPriorityQueue, assignPriority_EDF, t) != currTask) {
            //save progress for currTask
            currTask -> progress += t - startTime;
            //pop highest p. task and push currTask on
            currTask = popAndAddTPQ(currTask, schedule -> taskPriorityQueue, assignPriority_EDF, t);
            //parse execute
            parseExecution(currTask, t, outputFile);
            startTime = t;
        }
        
        //execution
        if(t - startTime + currTask -> progress == currTask -> exec_time) {
            //parse success
            parseCompletion(currTask, t, outputFile);
            //set progress of currTask to execTime
            currTask -> progress = currTask -> exec_time;
            //pop highest priority task from waiting queue and set to currTask
            currTask = getHighestPriorityTask(schedule->taskPriorityQueue, assignPriority_EDF, t);
            //parse execute 
            parseExecution(currTask, t, outputFile);
            startTime = t;
        }
    }
}   

int8_t freeScheduler(Scheduler * schedule){
    //free tasks first
    uint8_t i;
    for(i = 0; i < schedule -> taskCount; i++) 
        free(schedule -> tasks[i]);
    free(schedule -> tasks);

    //free everything else
    destroyTaskPriorityQueue(schedule -> taskPriorityQueue);
    destroyWaitingQueue(schedule -> waitingQueue);
    free(schedule);
    return 1;
}
