/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Window.c 
 */ 
#include "Window.h"
#include <GL/freeglut_std.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int16_t getTaskID(char * taskName, char ** map) {
    uint8_t i;
    for(i = 0; map[i] != NULL; i++) {
        if(strcmp(map[i], taskName) == 0)
            return i;
    }
    return -1;
}

void drawTaskAxis(char ** taskName, uint8_t taskCount, GLFWwindow * window) {
    //get dimensions of window
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    //get y position of each title
    //y-pos of task_i = titleY * i
    const int offset = height/100;
    const int titleY = (height - offset * 2)/taskCount;
    const int xPos = width/200;
    //titles on left at the height of each interval 
    uint8_t tID;
    for(tID = 0; tID < taskCount; tID++) {
        drawText(xPos, (tID + 1) * titleY, taskName[tID], window);
    }

    //draw row lines
}

void drawTimeAxis(unsigned int supertimeDuration, GLFWwindow * window) {
    //get dimensions of window
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    //get x position of each title
    const int offset = width/100;
    const int timeX = (width - offset * 2)/(supertimeDuration + 1);

    //titles on bottom
    unsigned int t;
    for(t = 0; t <= supertimeDuration; t++) {
        char tStr[10];
        sprintf(tStr, "%d", t);
        drawText((t + 1) * timeX, height/200, tStr, window);
    }

    //draw column lines
}

int8_t drawScheduleGraph(char ** taskNames, uint8_t taskCount, unsigned int supertimeDuration, const char * title, char * outputFileLoc) {
    
    //create list of id -> names
    char ** taskNameMap = (char **) malloc(sizeof(char *) * taskCount);

    //read file
    FILE * outputFile = fopen(outputFileLoc, "r");
    if(outputFile == NULL) 
        return 0;
    
    //create window
    GLFWwindow * window = glfwCreateWindow(1000, 500, title, NULL, NULL);
    
    //event loop
    while(!glfwWindowShouldClose(window)) {
        //draw time axis on bottom of screen
        drawTimeAxis(supertimeDuration, window);
    
        //draw task axis on left of screen
        drawTaskAxis(taskNames, taskCount, window);

        //read each line and call parseLine
        const uint8_t len = 40;
        char line[len];
        int16_t currTaskID = 0;
        unsigned int startTaskTime;
        while(fgets(line, len, outputFile)) {
            if(strcmp(line, "Scheduling Finishes") != 0) {
                parseLine(line, &currTaskID, supertimeDuration ,&startTaskTime, taskCount, taskNameMap, window);    
            }
        }
        glfwSwapBuffers(window);
    }
    fclose(outputFile);
    return 1;
}

void parseLine(char * line, int16_t * currTaskID, unsigned int supertimeDuration, unsigned int * startT, uint8_t taskCount, char ** taskNameMap, GLFWwindow * window) {
    //get time task_name command
    char lineCpy[strlen(line)];
    strcpy(lineCpy, line);

    unsigned int time = atoi(strtok(lineCpy, " "));
    char * taskName = strtok(NULL, " ");
    char * command = strtok(NULL, " ");

    //check what command equals
    //executes -> change currTaskID to whatever task executed and change startTaskTime to the t in the line
    //success -> drawSuccess at t and  currTaskID to 0 and drawTaskBar for starT -> currT
    //miss -> red triangle and if currTask missed then change currTask and drawTaskBar for startT -> currT

    if(strcmp(command, "Executes") == 0) {
        int16_t id = getTaskID(taskName, taskNameMap); 
        if(id != -1) {
            *currTaskID = id;
            *startT = time;
        }
    } else if(strcmp(command, "Success") == 0) {
        drawSuccess(time, *currTaskID, supertimeDuration, taskCount, window);
        //draw task bar
        for(; time >= *startT; time--) {
            drawTaskBar(time, *currTaskID, supertimeDuration, taskCount, window);
        }
        *currTaskID = -1;
    } else if(strcmp(command, "Miss") == 0) {
        drawMiss(time, *currTaskID, supertimeDuration, taskCount, window);
        if(strcmp(taskName, taskNameMap[*currTaskID]) == 0) {
            //missed task is current task
            for(; time >= *startT; time--) {
                drawTaskBar(time, *currTaskID, supertimeDuration, taskCount, window);
            }   
        }
        *currTaskID = -1;
    } else {
        //error
    }
}
