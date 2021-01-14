/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 Coursework
 * File: Shapes.h is the header file for the shapes drawn on the window. These shapes are the success green triangle, the miss red diamond, and the blue bar for the task's duration
 */

#include "Positioning.h"
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

/* DESCR: Draws a green triangle representing a successful task completion
 * PARAM: time is the time the success happened: x coordinate
 * PARAM: taskID is the completed task's graphical ID: y coordinate
 * PARAM: supertimeDuration is the supertime duration and the x's plot intervals depend on this
 * PARAM: taskCount is the number of tasks displayed on the graph and the y's plot intervals depend on this
 * PARAM: the window is the window being drawn on
 */ 
void drawSuccess(unsigned int time, uint8_t taskID, unsigned int supertimeDuration, uint8_t taskCount, GLFWwindow * window);

/* DESCR: Draws a red diamond representing a missed task
 * PARAM: time is the time the miss happened: x coordinate
 * PARAM: taskID is the missed task's graphical ID: y coordinate
 * PARAM: supertimeDuration is the supertime duration and the x's plot intervals depend on this
 * PARAM: taskCount is the number of tasks displayed on the graph and the y's plot intervals depend on this
 * PARAM: the window is the window being drawn on
 */
void drawMiss(unsigned int time, uint8_t taskID, unsigned int supertimeDuration, uint8_t taskCount, GLFWwindow * window);

/* DESCR: Draws a taskbar for the currTask at currTime
 * PARAM: time is the current time: x coordinate
 * PARAM: taskID is the current task's graphical ID: y coordinate
 * PARAM: supertimeDuration is the supertime duration and the x's plot intervals depend on this
 * PARAM: taskCount is the number of tasks displayed on the graph and the y's plot intervals depend on this
 * PARAM: the window is the window being drawn on
 */ 
void drawTaskBar(unsigned int time, uint8_t taskID, unsigned int supertimeDuration, uint8_t taskCount, GLFWwindow * window);

/* DESCR: Draws text at a position on the window
 * PARAM: xPos is the x position of the beginning of the text
 * PARAM: yPos is the y position of the beginning of the text
 * PARAM: text is the text drawn on the screen
 * PARAM: window is the window being drawn on
 */ 
void drawText(unsigned int xPos, unsigned int yPos, char * text, GLFWwindow * window);
