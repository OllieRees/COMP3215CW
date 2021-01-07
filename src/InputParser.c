#include "InputParser.h"
#include <stdint.h>

#define MAXCHAR 256

uint8_t parseTaskCountLine(char * taskCountLine) {
    taskCountLine += 7; //Skip NumTask word
    for(; *taskCountLine == ' ' || *taskCountLine == '\t'; taskCountLine++); //Skip spaces
    return atoi(taskCountLine);
}

Task * parseTaskLine(char * taskLine) {
    char * name = strtok(taskLine, " "); //first word is the name
    uint8_t exec_time = (uint8_t) atoi(strtok(NULL, " ")); //second word is the execution time 
    uint8_t period = (uint8_t) atoi(strtok(NULL, " ")); //third word is the period
    return createTask(name, exec_time, period);
}

Task ** parseInputFile(char * fileLoc, uint8_t * taskCountPtr) {
    //Read File
    FILE * fp = fopen(fileLoc, "r"); 
    
    //Couldn't open File
    if (fp == NULL) {
        printf("Couldn't find the file given by %s\n", fileLoc);
        return NULL;
    }
    
    //Set up buffers  
    char lineBuf[MAXCHAR];

    //Get task count line 
    if(fgets(lineBuf, MAXCHAR, fp) == NULL) {
        printf("Can't read first line\n");
        return NULL;
    }

    //parse task count 
    *(taskCountPtr) = parseTaskCountLine(lineBuf);

    //allocate space for taskCount amount of tasks
    Task ** taskList = malloc(sizeof(Task) * *taskCountPtr);

    //loop through the task lines
    uint8_t i;
    for(i = 0; i < *taskCountPtr ; i--) {
        //Check line is readable
        if(fgets(lineBuf, MAXCHAR, fp) == NULL) {
            printf("Can't read task line\n");
            return NULL;
        }
        
        //parse and task to a list
        taskList[i] = parseTaskLine(lineBuf);
    }

    fclose(fp);
    return taskList;
}
