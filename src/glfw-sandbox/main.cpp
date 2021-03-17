// Documentation for GLFW: https://www.glfw.org/documentation.html


#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Will give use GLFW + GL

#include <iostream>


void opengl_intialize(int width, int height, int fov) {
    // Depth
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);

    // Color
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Lighting
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    // Texture related
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    // Blending
    glBlendFunc(GL_ONE, GL_ONE);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glViewport(0, 0, width, height);            // Set viewport region.
    glMatrixMode(GL_PROJECTION);                // Switch to Projection-Matrix mode.
    glLoadIdentity();                           // Reset the Projection-Matrix.

    gluPerspective(fov, width / (double)height, 0.09, 25);

    glMatrixMode(GL_MODELVIEW);                 // Select the Modelview-Matrix
}

void drawGrid(float xSize, float zSize)
{
    glColor3ub(255, 255, 255);
    glLineWidth(1);

    glBegin(GL_LINES);
    for (int i = -zSize / 2.0; i <= zSize / 2.0; i++) {
        glVertex3f(-xSize/2.0, 0, i);
        glVertex3f(xSize/2.0, 0, i);
    }

    for (int i = -xSize / 2.0; i <= xSize / 2.0; i++) {
        glVertex3f(i, 0, -zSize / 2.0);
        glVertex3f(i, 0, zSize / 2.0);
    }

    glEnd();

    glLineWidth(2);

    glBegin(GL_LINES);
        glColor3ub(255, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);

        glColor3ub(0, 255, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glColor3ub(0, 0, 255);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);
    glEnd();

    glColor3ub(255, 255, 255);

}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0);
        glVertex3f(0, 0, 0);

        glColor3ub(0, 255, 0);
        glVertex3f(1, 0, 0);

        glColor3ub(0, 0, 255);
        glVertex3f(0.5, 1, 0);
    glEnd();
}

void drawWheel(int lod) {
    glBegin(GL_POLYGON);

        glVertex3f(0, 0, 0);

        for (int i = 0; i <= lod; i++)
        {
            glVertex3f(std::cos((i * 360 / (float)lod) * 3.14/180.0), std::sin((i * 360 / (float)lod)* 3.14/180.0), 0);
        }

    glEnd();
}

int main() {

    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW library" << std::endl;
        return 1;
    }

    const int resolutionWidth = 1280;
    const int resolutionHeight = 720;
    window = glfwCreateWindow(resolutionWidth, resolutionHeight,    // Resolution
                              "GLFW playground",                    // Title
                              NULL,                                 // Monitor for fullscreen
                              NULL);                                // Window to steal OpenGL context from - in most cases NULL

    if (!window)
    {
        std::cout << "Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        return 2;
    }

    // Bind the window and OpenGL context
    glfwMakeContextCurrent(window);

    opengl_intialize(resolutionWidth, resolutionHeight, 60);

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
        
        triangleZ -= 0.001f;

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
                drawWheel(8);
                glPopMatrix();
            }

            state = glfwGetKey(window, GLFW_KEY_T);
            if (state == GLFW_PRESS) {
                glTranslatef(-1, 0, 0);
                glRotatef(std::sin(time) * 10, 0, 0, 1);
                drawTriangle();

                glPushMatrix();                
                {
                    glTranslatef(1, 0, 0);
                    glRotatef(std::sin(time) * 5, 0, 0, 1);
                    drawTriangle();
             
                    glPushMatrix();
                    {
                        glTranslatef(1, 0, 0);
                        glRotatef(std::sin(time) * 2, 0, 0, 1);
                        glScalef(1, 1.5, 1);
                        drawTriangle();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
        
        

        drawGrid(10, 10);

        // This basically means - show what we've been working on since glClear
        glfwSwapBuffers(window);

        // Check for GLFW events - keyboard, mouse, ...
        glfwPollEvents();
    }

    // Proper way to deinitialize GLFW - releases context and so on
    glfwTerminate();

    return 0;
}
