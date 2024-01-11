#include <../src/graphics/graphics.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow *graphicsInit(GLFWwindow *win, int w, int h){
    // basic setup stuff
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // make the window and set the rendering context
    win = glfwCreateWindow(w, h, "Test", NULL, NULL);
    if(win == NULL){
        printf("Failed to initialize GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(win);
    
    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    } 

    // set the viewport
    glViewport(0, 0, w, h);

    return win;
}