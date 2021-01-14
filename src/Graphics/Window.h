/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Window.h is the header file for the drawing of the window and parsing the output file to graphics.
 */

#include "Shapes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>


/* DESCR: Draws the task axis titles along the y-axis.
 * PARAM: taskNames are the name of the tasks represented in the scheduler graph
 * PARAM: taskCount is the number of tasks in the list of task names
 * PARAM: window is the window the task axis is drawn on
 */ 
void drawTaskAxis(char ** taskNames, uint8_t taskCount, GLFWwindow * window);

/* DESCR: Draws the time axis numbers along the x-axis
 * PARAM: supertimeDuration is the duration of the supertime period in 10ms, thus the number of intervals in the x axis
 * PARAM: window is the window the time axis is drawn on
 */ 
void drawTimeAxis(unsigned int supertimeDuration, GLFWwindow * window);

/* DESCR: Draws the initial window before the schedule has run 
 * PARAM: taskNames are the name of the tasks represented in the scheduler graph
 * PARAM: taskCount is the number of tasks in the list of tasks
 * PARAM: supertimeDuration is the duration of the supertime period in 10ms, thus the number of intervals in the x axis
 * PARAM: title is the title of the window
 * PARAM: outputFileLoc is the location of the output file produced by the scheduler
 * RETURN: 1 if the window could be drawn successfully
 */ 
int8_t drawScheduleGraph(char ** taskNames, uint8_t taskCount, unsigned int supertimeDuration, const char * title, char * outputFileLoc);

/* DESCR: parses a line from the output file drawing the correct shape on the output file
 * PARAM: line is the line being parsed
 * PARAM: the currTaskID is the id of the currentTask
 * PARAM: supertimeDuration is the total time run by the scheduler
 * PARAM: startT is the temporary start time of the current task
 * PARAM: taskCount is the number of tasks run by the scheduler and present in the taskNameMap
 * PARAM: taskNameMap is the mapping from task id to task name
 * PARAM: window is the window being drawn on
 */ 
void parseLine(char * line, int16_t * currTaskID, unsigned int supertimeDuration, unsigned int * startT,  uint8_t taskCount, char ** taskNameMap, GLFWwindow * window);
