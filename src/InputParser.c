#include "InputParser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 256

uint8_t parseTaskCountLine(char * taskCountLine) {
    taskCountLine += 8; //Skip NumTasks word
    for(; *taskCountLine == ' ' || *taskCountLine == '\t'; taskCountLine++); //Skip spaces
    return atoi(taskCountLine);
}

Task * parseTaskLine(char * taskLine) {
    Task * task = malloc(sizeof(Task));
    //split into words
    //first word is the name
    //second word is the execution time
    //third word is the period
   
    int taskLineLen = strlen(taskLine);
    char * taskLineCpy = calloc(taskLineLen + 1, sizeof(char));
    strncpy(taskLineCpy, taskLine, taskLineLen);
    
    task -> name = strtok(taskLineCpy, " ");
    task -> exec_time = atoi(strtok(NULL, " "));
    task -> period = atoi(strtok(NULL, " "));
    return task;
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
    *taskCountPtr = parseTaskCountLine(lineBuf);

    //allocate space for taskCount amount of tasks
    Task ** taskList = malloc(sizeof(Task) * *taskCountPtr);

    //loop through the task lines
    uint8_t i;
    for(i = 0; i < *taskCountPtr ; i++) {
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
