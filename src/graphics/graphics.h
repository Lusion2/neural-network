/*
 * Graphics initialization for visualization of the network
 */
#ifndef __AP_COMPSCI_AI_GRAPHICS_H
#define __AP_COMPSCI_AI_GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
 * initialized GLFW and returns the pointer to a window
 */
GLFWwindow *graphicsInit(GLFWwindow *win, int w, int h);

#endif // __AP_COMPSCI_AI_GRAPHICS_H