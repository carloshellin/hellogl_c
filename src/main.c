#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "types.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "rglfw.c"
#include <GL/gl.h>

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char* argv[])
{
    const int screen_width = 640;
    const int screen_height = 480;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "GLFW3: Can not initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("GLFW3: GLFW initialized successfully\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "Hello OpenGL", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("GLFW3: Window created successfully\n");
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwSetWindowPos(window, mode->width / 2 - screen_width / 2, mode->height / 2 - screen_height / 2);

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glViewport(0, 0, screen_width, screen_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screen_width, screen_height, 0, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.96f, 0.96f, 0.96f, 1.0f);

    u8 r = 80;
    u8 g = 80;
    u8 b = 80;
    u8 a = 255;

    f32 size_x = 100.0f;
    f32 size_y = 100.0f;

    f32 position_x = (screen_width / 2.0f) - (size_x / 2.0f);
    f32 position_y = (screen_height / 2.0f) - (size_y / 2.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            glColor4ub(r, g, b, a);

            glVertex2f(position_x, position_y);
            glVertex2f(position_x, position_y + size_y);
            glVertex2f(position_x + size_x, position_y + size_y);

            glVertex2f(position_x, position_y);
            glVertex2f(position_x + size_x, position_y + size_y);
            glVertex2f(position_x + size_x, position_y);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();   

    exit(EXIT_SUCCESS);
}