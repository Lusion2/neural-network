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

/*
 * Shader structure, only variable is an ID, 
 * this structure is made to be explicit
*/
typedef struct Shader Shader;
struct Shader{
    unsigned int ID;
};

/*
 * abstract class for holding VAO, VBO, and shaders
 */
typedef struct vertexObject vertexObject;
struct vertexObject{
    // vertex objects
    GLuint VBO, VAO, EBO;

    // base shader program
    Shader shader;
};


/*
 * Creates a shader program using given shader files
 *
 * vsPath: vertex shader file
 * fsPath: fragment shader file
 */
void ShaderInit(Shader *shader, const char *vsPath, const char *fsPath);

/*
 * initializes a basic vertexObject as shown above
 */
vertexObject *vertexObjectInit(vertexObject *win);

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