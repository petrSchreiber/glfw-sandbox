// Documentation for GLFW: https://www.glfw.org/documentation.html

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Will give use GLFW + GL

#include <iostream>
#include "drawings.hpp"
#include "engine.hpp"
#include "controls.hpp"
#include "controls_static.hpp" // Testing
#include "frame.hpp"


int main() {

    WindowCreator windowObject(1280, 720, 60);
    auto window = windowObject.getWindow();
    Controls controls(window);
    
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
    
    Frame frame{};

    while (!glfwWindowShouldClose(window))
    {
        frame.Begin();
            // Let's clear color and depth memory
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Load identity matrix for modelview
            glLoadIdentity();

            // Auxiliary camera
            gluLookAt(cameraX, cameraY, cameraZ,    // From X, Y, Z
                      targetX, targetY, targetZ,    // To
                       0, 1, 0);                    // Up vector

            // Rendering will go here
        
            triangleZ -= 0.001f; 

            rotateZ -= 0.1f;
            rotateY += 0.1f;

            time += 0.1f;

            glPushMatrix();       
            {
            
                if (ControlsStatic::arrowUP(window)) // Static control without instancing
                {
                    cameraZ -= 0.1;
                    targetZ -= 0.1;
                }
            
                if (controls.arrowDOWN()) // Controls with instancing
                {
                    cameraZ += 0.1;
                    targetZ += 0.1;
                }

                if (controls.arrowLEFT())
                {
                    cameraX -= 0.1;
                    targetX -= 0.1;
                }

                if (controls.arrowRIGHT())
                {
                    cameraX += 0.1;
                    targetX += 0.1;
                }

                if (controls.keyC())
                {
                    glPushMatrix();
                    glTranslatef(0, 0, 1);
                    DrawObjects::wheel(8); // calling a static function
                    glPopMatrix();
                }
            
                if (controls.keyT()) {
                    glTranslatef(-1, 0, 0);
                    glRotatef(std::sin(time) * 10, 0, 0, 1);
                    DrawObjects::triangle(); // calling a static function

                    glPushMatrix();                
                    {
                        glTranslatef(1, 0, 0);
                        glRotatef(std::sin(time) * 5, 0, 0, 1);
                        DrawObjects::triangle(); // calling a static function
             
                        glPushMatrix();
                        {
                            glTranslatef(1, 0, 0);
                            glRotatef(std::sin(time) * 2, 0, 0, 1);
                            glScalef(1, 1.5, 1);
                            DrawObjects::triangle(); // calling a static function
                        }
                        glPopMatrix();
                    }
                    glPopMatrix();
                }
            }
            glPopMatrix();
        
            DrawObjects::grid(10, 10); // calling a sttic function

            // This basically means - show what we've been working on since glClear
            glfwSwapBuffers(window);

            // Check for GLFW events - keyboard, mouse, ...
            glfwPollEvents();
        frame.End();

        std::cout << "Sweet FPS: " << frame.GetFrameRate() << std::endl;
    }

    // Proper way to deinitialize GLFW - releases context and so on
    glfwTerminate();

    return 0;
}
