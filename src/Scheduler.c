/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Scheduler.c is the implementation of the scheduler structure, assigning the schedulers members and running the scheduler.
 */ 
#include "Scheduler.h"

Scheduler * createScheduler(Task ** tasks, uint8_t taskCount) {
    Scheduler * schedule = (Scheduler *) malloc(sizeof(Scheduler));
    schedule -> tasks = tasks;
    schedule -> taskCount = taskCount;
    schedule -> taskPriorityQueue = createTaskPriorityQueue(tasks, taskCount, assignPriority_RMS);
    schedule -> waitingQueue = createFilledWaitingQueue(tasks, taskCount, taskCount); 
    
    //add all tasks to waiting queue
    return schedule;
}

static void taskExecuted(Task * currTask, unsigned int time, unsigned int * startTime, FILE * outputFile) {
    printf("task being executed : %s\n", currTask -> name);
    parseExecution(currTask, time, outputFile);
    *startTime = time;
}

static void runMiss(Task * currTask, unsigned int time, unsigned int startTime, SchedulingAlgorithm priorityFunc, FILE * outputFile, Scheduler * schedule) {
    //pop tasks that have their deadline now
    int taskCount = schedule -> waitingQueue -> elements[findKey(time, schedule -> waitingQueue)].taskCount;
    Task ** tasks = popAllWQ(time, schedule -> waitingQueue);
    //run if task count is greater than 0
    uint8_t i;
    for(i = 0; i < taskCount; i++) {
        //special case for currTask if it's run into its deadline
        if(currTask == tasks[i]) {
            printf("Curr Task popped from WQ at time %d and start time %d with progress %d\n", time, startTime, currTask -> progress);
            if(time - startTime + currTask -> progress == currTask -> exec_time) {
                parseCompletion(currTask, time, outputFile);
            } else {
                parseMiss(currTask, time, outputFile);
                printf("%d %s miss\n", time, tasks[i] -> name);
            }
            insertTPQ(currTask, schedule -> taskPriorityQueue, priorityFunc, time);
            currTask = NULL;
        }
        //other tasks than currTask
        else {
            printf("Progress: %d; EXEC: %d\n", tasks[i] -> progress, tasks[i] -> exec_time);
            if(tasks[i] -> progress != tasks[i] -> exec_time) {
                parseMiss(tasks[i], time, outputFile);
                printf("%d %s miss\n", time, tasks[i] -> name);
            } else {
                insertTPQ(tasks[i], schedule -> taskPriorityQueue, priorityFunc, time);
            }
        }
        //reset progress to 0
        tasks[i] -> progress = 0;
        //add task back to the waiting queue with new deadline
        pushWQ(tasks[i], time + tasks[i] -> period, schedule -> waitingQueue);
    }
}

static void runInterrupt(Task ** currTask, unsigned int time, unsigned int * startTime, SchedulingAlgorithm * priorityFunc, FILE * outputFile, Scheduler * schedule) {
        printf("%d %s interrupt\n", time, currTask[0] -> name);
        //save progress for currTask
        currTask[0] -> progress += time - *startTime;
        //pop highest p. task and push currTask on
        *currTask = popAndAddTPQ(*currTask, schedule -> taskPriorityQueue, priorityFunc, time);
        if(currTask[0] != NULL) {
            //parse execute
            taskExecuted(*currTask, time, startTime, outputFile);
        }
}

static void runCompletion(Task ** currTask, unsigned int time, unsigned int * startTime, SchedulingAlgorithm * priorityFunc, FILE * outputFile, Scheduler * schedule) {
    printf("%d %s success\n", time, currTask[0] -> name);
    //parse success
    parseCompletion(*currTask, time, outputFile);
    //set progress of currTask to execTime
    currTask[0] -> progress = currTask[0] -> exec_time;
    //pop highest priority task from waiting queue and set to currTask
    printf("\nTPQ\n");
    printTPQ(schedule -> taskPriorityQueue);
    printf("\n\n");
    *currTask = getHighestPriorityTask(schedule->taskPriorityQueue, priorityFunc, time);
    if(currTask[0] != NULL) {
        //parse execute
        taskExecuted(*currTask, time, startTime, outputFile);
    }
}

void runScheduler(int supertime, char * fileLoc, SchedulingAlgorithm * priorityFunc, Scheduler * schedule){
    //set up output file
    FILE * outputFile = createOutputFile(fileLoc);  
    printWaitingQueue(schedule -> waitingQueue);

    //set up current task
    Task * currTask = getHighestPriorityTask(schedule -> taskPriorityQueue, priorityFunc, 0); 
    
    //time loop
    unsigned int startTime = 0; //used to save start time of current task
    unsigned int t;
    for(t = 0; t < supertime; t++) {
        //printf("%d", t);
        //printf("\n\nWQ");
        //printWaitingQueue(schedule -> waitingQueue);
        //printf("\n\nTPQ\n\n");
        //printTPQ(schedule -> taskPriorityQueue);
        //printf("\n\n");
        
        //Miss
        if(peekWQ(t, schedule -> waitingQueue) != NULL)
            runMiss(currTask, t, startTime, priorityFunc, outputFile, schedule);

        //tasks have ended -> check if any new tasks have been added to the p. queue else continue
        if(currTask == NULL) {
            if(peekHighestPriorityTask(schedule -> taskPriorityQueue) != NULL) {
                //get currTask at top
                currTask = getHighestPriorityTask(schedule -> taskPriorityQueue, priorityFunc, t);
                taskExecuted(currTask, t, &startTime, outputFile);
            } else {
                //no more tasks to run until tasks have been loaded off waiting queue 
                continue;
            }
        }

        //execution
        if(t - startTime + currTask -> progress == currTask -> exec_time) {
            runCompletion(&currTask, t, &startTime, priorityFunc, outputFile, schedule);
        }
        else {
            //interrupt
            if(peekHighestPriorityTask(schedule -> taskPriorityQueue) != NULL) {
                if(priorityFunc(peekHighestPriorityTask(schedule -> taskPriorityQueue), t) < priorityFunc(currTask, t)) {
                    runInterrupt(&currTask, t, &startTime, priorityFunc, outputFile, schedule);
                }
            }     
        }
    }
    closeOutputFile(outputFile);
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
