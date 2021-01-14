/* Author: Ollie Rees
* Project: COMP3215 Coursework
* File: Positioning.h contains the interfaces for translating time to x position and taskID to y position
*/
#include <GLFW/glfw3.h>
#include <GL/glut.h>

/* DESCR: Get x position of a cell based on the time
 * PARAM: time is the time the x position is mapped to
 * PARAM: supertimeDuration is the supertime duration and the x's plot intervals depend on this
 * PARAM: window is the window which contains the cell representing time 
 * RETURN: the time's x position
 */ 
unsigned int getXPos(unsigned int time, unsigned int supertimeDuration, GLFWwindow * window);

/* DESCR: Get y position of a cell based on the taskID
 * PARAM: task id is the task id the y position is mapped to
 * PARAM: window is the window which contains the cell representing the task
 * PARAM: taskCount is the number of tasks displayed on the graph and the y's plot intervals depend on this
 * RETURN: the task's y position
 */ 
unsigned int getYPos(uint8_t taskID, uint8_t taskCount, GLFWwindow * window);

