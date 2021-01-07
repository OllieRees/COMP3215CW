#include "InputParser.h"
#include "Scheduler.h"

int main(int argc, char ** argv) {
    uint8_t taskCount;
    Task ** tasks = parseInputFile(argv[1], &taskCount);
    uint8_t i;
    for(i = 0; i < taskCount; i++) {
        printf("%s %d %d\n", tasks[i] -> name, tasks[i] -> exec_time, tasks[i] -> period);
    }
     
    //if argc < 4
        //printf("ERROR\n");
    //uint8_t taskCount;
    //Task ** tasks = parseInputFile(argv[1], &taskCount);
    //Scheduler * scheduler = createScheduler(tasks, taskCount);
    //runScheduler(argv[2], argv[3], scheduler);
}
