/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Task.c is the implementation of the task structure's behaviour
 * TODO: More on the file
 */ 
#include "Task.h"

Task * createTask(char * name, uint8_t exect_time, uint8_t period) {
    Task * task = malloc(sizeof(Task));
    task -> name = name;
    task -> exec_time = exect_time;
    task -> period = period;
    task -> progress = 0;
    return task;
}

void updateProgress(Task * task, int startTime, int currentTime) {
    task -> progress = currentTime - startTime;
}

void destroyTask(Task * task) {
    free(task -> name);
    free(task);
}
