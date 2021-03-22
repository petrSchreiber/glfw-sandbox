// Documentation for GLFW: https://www.glfw.org/documentation.html

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Will give use GLFW + GL

#include <iostream>
#include "drawings.hpp"
#include "engine.hpp"



int main() {

    //DrawObjects drawx;
    WindowCreator windowObject(1280, 720, 60);
    auto window = windowObject.getWindow();
    
    glfwMakeContextCurrent(window);
    windowObject.opengl_intialize();

    float triangleZ = 0;
    float rotateZ = 0;
    float rotateY = 0;

    float time = 0;

    float cameraX, cameraY, cameraZ;
    float targetX, targetY, targetZ;

    cameraX = 0;
    cameraY = 1.7;
    cameraZ = 0;

    targetX = 0;
    targetY = 1.7;
    targetZ = -1;
    int state = 0;
    
    while (!glfwWindowShouldClose(window))
    {
        // Let's clear color and depth memory
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Load identity matrix for modelview
        glLoadIdentity();

        // Auxiliary camera
        gluLookAt(cameraX, cameraY, cameraZ,    // From X, Y, Z
                  targetX, targetY, targetZ,    // To
                   0, 1, 0);                    // Up vector

        // Rendering will go here
        
        triangleZ -= 0.001f; //What is the difference between 0.001f and 0.001? Don't know how to google this question :( 

        rotateZ -= 0.1f;
        rotateY += 0.1f;

        time += 0.1f;


        glPushMatrix();       
        {
            state = glfwGetKey(window, GLFW_KEY_UP);
            if (state == GLFW_PRESS)
            {
                cameraZ -= 0.1;
                targetZ -= 0.1;
            }

            state = glfwGetKey(window, GLFW_KEY_DOWN);
            if (state == GLFW_PRESS)
            {
                cameraZ += 0.1;
                targetZ += 0.1;
            }

            state = glfwGetKey(window, GLFW_KEY_LEFT);
            if (state == GLFW_PRESS)
            {
                cameraX -= 0.1;
                targetX -= 0.1;
            }

            state = glfwGetKey(window, GLFW_KEY_RIGHT);
            if (state == GLFW_PRESS)
            {
                cameraX += 0.1;
                targetX += 0.1;
            }


            state = glfwGetKey(window, GLFW_KEY_C);
            if (state == GLFW_PRESS)
            {
                glPushMatrix();
                glTranslatef(0, 0, 1);
                DrawObjects::wheel(8);
                glPopMatrix();
            }

            state = glfwGetKey(window, GLFW_KEY_T);
            if (state == GLFW_PRESS) {
                glTranslatef(-1, 0, 0);
                glRotatef(std::sin(time) * 10, 0, 0, 1);
                DrawObjects::triangle();

                glPushMatrix();                
                {
                    glTranslatef(1, 0, 0);
                    glRotatef(std::sin(time) * 5, 0, 0, 1);
                    DrawObjects::triangle();
             
                    glPushMatrix();
                    {
                        glTranslatef(1, 0, 0);
                        glRotatef(std::sin(time) * 2, 0, 0, 1);
                        glScalef(1, 1.5, 1);
                        DrawObjects::triangle();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
        
        DrawObjects::grid(10, 10);

        // This basically means - show what we've been working on since glClear
        glfwSwapBuffers(window);

        // Check for GLFW events - keyboard, mouse, ...
        glfwPollEvents();
    }

    // Proper way to deinitialize GLFW - releases context and so on
    glfwTerminate();

    return 0;
}
