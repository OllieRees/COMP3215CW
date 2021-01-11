#include "InputParser.h"
#include "Scheduler.h"

int main(int argc, char ** argv) {
    if (argc < 5) {
        printf("ERROR: Not enough arguements\n");
        return 1;
    }
    uint8_t taskCount;
    Task ** tasks = parseInputFile(argv[1], &taskCount);
    Scheduler * scheduler = createScheduler(tasks, taskCount);
    SchedulingAlgorithm * priorityFunc = atoi(argv[4]) == 0 ? assignPriority_RMS : assignPriority_EDF;
    runScheduler(atoi(argv[3]), argv[2], priorityFunc, scheduler);
    return 0;
}
