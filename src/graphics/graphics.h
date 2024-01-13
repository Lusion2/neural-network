/*
 * Graphics initialization for visualization of the network
 */
#ifndef __AP_COMPSCI_AI_GRAPHICS_H
#define __AP_COMPSCI_AI_GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// basic screen constants for quality of life
#define WIDTH       800
#define HEIGHT      600
#define WIDTH2      WIDTH/2                 // half width
#define HEIGHT2     HEIGHT/2                // half height

// base shaders
static const char *vertexShaderSource = "( \
    #version 330 core \
    layout (location = 0) in vec2 position; \
    void main() { \
        gl_Position = vec4(position, 0.0, 1.0); \
    } \
)";

static const char *fragmentShaderSource = "( \
    #version 330 core \
    out vec4 color; \
    void main() { \
        color = vec4(1.0, 1.0, 1.0, 1.0); // White color \
    } \
)";

/*
 * abstract class for holding VAO, VBO, and shaders
 */
typedef struct vertexObject vertexObject;
struct vertexObject{
    // vertex objects
    GLuint VBO, VAO;

    // base shader program
    GLuint shaderProg;
};

/*
 * initializes a basic vertexObject as shown above
 */
vertexObject *vertexObjectInit_TEST(vertexObject *win);


/*
 * initializes GLFW and returns the pointer to a window
 */
GLFWwindow *graphicsInit(GLFWwindow *win, int w, int h);

/*
 * draws a pixel at a specified point with color, r, g, b
 */
void pixelDraw(int x, int y, float r, float g, float b);

/*
 * draws an outline of a 10x10 graph
 */
void graphOutline(vertexObject *win);

#endif // __AP_COMPSCI_AI_GRAPHICS_H