// Documentation for GLFW: https://www.glfw.org/documentation.html

#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Will give use GLFW

#define GLEW_STATIC
#include <glew.h>       // Will give us the latest OpenGL available

#include <iostream>
#include "drawings/drawings.hpp"
#include "engine/engine.hpp"
#include "controls/controls.hpp"
#include "controls/controls_static.hpp" // Testing
#include "frame/frame.hpp"
#include "camera/camera.hpp"
#include <vector>
#include "vector3d/vector3d.hpp"
#include "logger/logger.hpp"


int main() {

    logger log;

    WindowCreator windowObject(1280, 720, 60);
    auto window = windowObject.getWindow();
    Controls controls(window);

    
        
    Frame frame{};

    Vector3d cameraPos[2] = { { 0, 1.7, 0 }, { 0, 2, -5 } };
    Vector3d cameraDirection[2] = { { 0, 0, 1 }, { 0, 0, 1 } };

    std::vector<CameraManager> cameras{};
    cameras.emplace_back("first person", cameraPos[0]);
    cameras.emplace_back("third person", cameraPos[1]);

    log.info("Test");
    log.warning("Test");
    log.error("Test");
    log.critical("Test");
    log.debug("Test");
    log.trace("Test");

    int activeCameraIndex = 0;

    float cameraAngle[2] = { 0, 0 };

   

    double fps = 5000;
    float time = 0;
    while (!glfwWindowShouldClose(window))
    {
        frame.Begin();
        
            // Let's clear color and depth memory
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Load identity matrix for modelview
            glLoadIdentity();

            // Auxiliary camera
            cameraDirection[activeCameraIndex].x = sinf(-cameraAngle[activeCameraIndex] * 0.0174533);
            cameraDirection[activeCameraIndex].z = cosf(-cameraAngle[activeCameraIndex] * 0.0174533);

            auto &activeCamera = cameras[activeCameraIndex];

            cameras[activeCameraIndex].SetLocation(cameraPos[activeCameraIndex]);
            cameras[activeCameraIndex].SetTarget(cameraPos[activeCameraIndex] + cameraDirection[activeCameraIndex]);

            cameras[activeCameraIndex].Apply();
            

            // Rendering will go here
        
            time += 1 / fps;

            glPushMatrix();       
            {
            
                if (ControlsStatic::arrowUP(window)) // Static control without instancing
                {
                    cameraPos[activeCameraIndex] = cameraPos[activeCameraIndex] + (cameraDirection[activeCameraIndex] / fps);
                }
            
                if (controls.arrowDOWN()) // Controls with instancing
                {
                    cameraPos[activeCameraIndex] = cameraPos[activeCameraIndex] - (cameraDirection[activeCameraIndex] / fps);
                }

                if (controls.arrowLEFT())
                {
                   cameraAngle[activeCameraIndex] -= 45 / fps;
                }

                if (controls.arrowRIGHT())
                {
                   cameraAngle[activeCameraIndex] += 45 / fps;
                }

                if (controls.keyC())
                {
                    glPushMatrix();
                    glTranslatef(0, 0, 1);
                    DrawObjects::wheel(8); // calling a static function
                    glPopMatrix();
                }


               
                if (ControlsStatic::keyF(window))
                {   
                    activeCameraIndex++;

                    if (activeCameraIndex > cameras.size() - 1) {
                        activeCameraIndex = 0;
                    }
                    
                    std::cout << "Camera active: " << cameras[activeCameraIndex].GetName() << std::endl;
                    
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
        fps = frame.GetFrameRate();

        //std::cout << "Sweet FPS: " << fps << std::endl;
    }

    // Proper way to deinitialize GLFW - releases context and so on
    glfwTerminate();

    return 0;
}
