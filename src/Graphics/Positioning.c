/* Author: Ollie Rees
 * Project: COMP3215 Coursework
 * File: Positioning.c contains the implementation of translating time to x position and taskID to y position
 */ 
#include "Positioning.h"

unsigned int getXPos(unsigned int time, unsigned int supertimeDuration, GLFWwindow * window) {
    //get dimensions of window
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    //get x position of each title
    const int offset = width/100;
    return (time + 1) * (width - offset * 2)/(supertimeDuration + 1);
}

unsigned int getYPos(uint8_t taskID, uint8_t taskCount, GLFWwindow * window) {
    //get window dimensions 
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    //get y 
    const int offset = height/100;
    return (taskID + 1) * (height - offset * 2)/taskCount;
}
