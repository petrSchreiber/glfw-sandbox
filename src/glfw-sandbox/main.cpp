// Documentation for GLFW: https://www.glfw.org/documentation.html

#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Will give use GLFW

#define GLEW_STATIC
#include <glew.h>       // Will give us the latest OpenGL available

#include <iostream>
#include "drawings.hpp"
#include "engine.hpp"
#include "controls.hpp"
#include "controls_static.hpp" // Testing
#include "frame.hpp"
#include "camera.hpp"


int main() {

    WindowCreator windowObject(1280, 720, 60);
    auto window = windowObject.getWindow();
    Controls controls(window);

    float time = 0;

    int state = 0;
    
    Frame frame{};

    CameraManager *activeCamera = nullptr;

    Vector3d cameraPos{ 0, 1.7, 0 };
    Vector3d cameraDirection{ 0, 0, -1 };
    
    Vector3d cameraPos2{ 0, 1.7, 0 };
    Vector3d cameraDirection2{ 0, 0, -1 };

    CameraManager firstPersonCamera{ cameraPos };
    CameraManager thirdPersonCamera{ cameraPos2 };

    activeCamera = &firstPersonCamera;

    

    float cameraAngle = 0;

    double fps = 5000;
    while (!glfwWindowShouldClose(window))
    {
        frame.Begin();
        
            // Let's clear color and depth memory
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Load identity matrix for modelview
            glLoadIdentity();

            // Auxiliary camera

            if (activeCamera == &thirdPersonCamera) {
                cameraDirection.x = sinf(-cameraAngle * 0.0174533);
                cameraDirection.z = cosf(-cameraAngle * 0.0174533);

                activeCamera->SetLocation(cameraPos2);
                activeCamera->SetTarget(cameraPos2 + cameraDirection2);

                activeCamera->Apply();
                
            }
            else {
                cameraDirection.x = sinf(-cameraAngle * 0.0174533);
                cameraDirection.z = cosf(-cameraAngle * 0.0174533);

                activeCamera->SetLocation(cameraPos);
                activeCamera->SetTarget(cameraPos + cameraDirection);

                activeCamera->Apply();
                
            }

            

            // Rendering will go here
        
            time += 1 / fps;

            glPushMatrix();       
            {
            
                if (ControlsStatic::arrowUP(window)) // Static control without instancing
                {
                    cameraPos = cameraPos + (cameraDirection / fps);
                }
            
                if (controls.arrowDOWN()) // Controls with instancing
                {
                    cameraPos = cameraPos - (cameraDirection / fps);
                }

                if (controls.arrowLEFT())
                {
                   cameraAngle -= 45 / fps;
                }

                if (controls.arrowRIGHT())
                {
                   cameraAngle += 45 / fps;
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
                    std::cout << "Camera switch" << std::endl;
                    if (activeCamera == &thirdPersonCamera)
                        activeCamera = &firstPersonCamera;
                    else if (activeCamera == &firstPersonCamera)
                        activeCamera = &thirdPersonCamera;
                    else{}
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
