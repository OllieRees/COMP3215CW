/* Author: Ollie Rees (or1g18)
 * Project: COMP3215 coursework
 * File: Shapes.c is the implementation of methods used to draw on to the screen.
 */ 
#include "Shapes.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>

void drawSuccess(unsigned int time, uint8_t taskID, unsigned int supertimeDuration, uint8_t taskCount, GLFWwindow * window) {
    //draw green triangle at (x, y) 

    //get positions
    unsigned int x = getXPos(time,  supertimeDuration, window);
    unsigned int diffX = (getXPos(time + 1, supertimeDuration, window) - x)/2;
    unsigned int y = getYPos(taskID, taskCount, window);
    unsigned int diffY = (getYPos(taskID + 1, taskCount, window) - y)/2;

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f); //green
        glVertex2f(x, y + diffY);
        glVertex2f(x - diffX, y - diffY);
        glVertex2f(x + diffX, y - diffY);
    glEnd();
}


void drawMiss(unsigned int time, uint8_t taskID, unsigned int supertimeDuration, uint8_t taskCount, GLFWwindow * window) {

    //get positions
    unsigned int x = getXPos(time, supertimeDuration, window);
    unsigned int diffX = (getXPos(time + 1, supertimeDuration, window) - x)/2;
    unsigned int y = getYPos(taskID, taskCount, window);
    unsigned int diffY = (getYPos(taskID + 1, taskCount, window) - y)/2;
    
    //draw red diamond
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x - diffX, y);
        glVertex2f(x + diffX, y);
        glVertex2f(x, y - diffY);
        glVertex2f(x, y + diffY);
    glEnd();
}

void drawTaskBar(unsigned int time, uint8_t taskID, unsigned int supertimeDuration, uint8_t taskCount, GLFWwindow * window) {

    //get positions
    unsigned int startX = getXPos(time, supertimeDuration, window);
    unsigned int endX = getXPos(time + 1, supertimeDuration, window);
    unsigned int y = getYPos(taskID, taskCount, window);
    unsigned int diffY = (getYPos(taskID + 1, taskCount, window) - y)/2;
    
    //draw blue rectangle
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(startX, y + diffY);
        glVertex2f(startX, y - diffY);
        glVertex2f(endX, y);
        glVertex2f(endX, y);
    glEnd();
}

void drawText(unsigned int xPos, unsigned int yPos, char * text, GLFWwindow * window) {
    glRasterPos2d(xPos, yPos);
    char * c;
    for (c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);  // Updates the position
    }
}
