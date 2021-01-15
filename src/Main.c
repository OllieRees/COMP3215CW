#include "InputParser.h"
#include "Scheduler.h"

int main(int argc, char ** argv) {
    //check if enough args
    if (argc < 5) {
        printf("ERROR: Not enough arguements\n");
        return 1;
    }

    //get tasks
    uint8_t taskCount;
    Task ** tasks = parseInputFile(argv[1], &taskCount);
    if(tasks == NULL) {
        printf("Couldn't read input file\n");
        return 1;
    }
    
       //scheduler
    Scheduler * scheduler = createScheduler(tasks, taskCount);
    SchedulingAlgorithm * priorityFunc = atoi(argv[4]) == 0 ? assignPriority_RMS : assignPriority_EDF;
    runScheduler(atoi(argv[3]), argv[2], priorityFunc, scheduler);
    
    //draw final window
    
    freeScheduler(scheduler);
    return 0;
}
