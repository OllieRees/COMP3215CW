#include "Task.h"
#include <stdint.h>

Task * createTask(char * name, uint8_t exec_time, uint8_t period) {
    Task * newTask = malloc(sizeof(Task));
    newTask -> name = name;
    newTask -> exec_time = exec_time;
    newTask -> period = period;
    return newTask;
}

int destroyTask(Task * task) {
    //check if task is in use somewhere -> check scheduler?
    //TODO: Implement check if it can be freed
    
    //free task
    free(task -> name);
    free(task);
    return 1;
}
