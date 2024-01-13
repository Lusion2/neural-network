#include <../src/graphics/graphics.h>
#include <stdio.h>
#include <stdlib.h>

vertexObject *vertexObjectInit_TEST(vertexObject *win){
    // compile and link the base shader program
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(fs);

    win->shaderProg = glCreateProgram();
    glAttachShader(win->shaderProg, vs);
    glAttachShader(win->shaderProg, fs);
    glLinkProgram(win->shaderProg);
    glDeleteShader(vs);
    glDeleteShader(fs);
    // Define the graph data
    GLfloat vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    // Create a Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &win->VAO);
    glGenBuffers(1, &win->VBO);

    // Bind the VAO
    glBindVertexArray(win->VAO);

    // Bind the VBO and set the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, win->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return win;
}

GLFWwindow *graphicsInit(GLFWwindow *win, int w, int h)
{
    // basic setup stuff
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // make the window and set the rendering context
    win = glfwCreateWindow(w, h, "AP CSP Final Project: Neural Network", NULL, NULL);
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

    // clear color
    glClearColor(0.192f, 0.243f, 0.388f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    return win;
}

void pixelDraw(int x, int y, float r, float g, float b){
    glBegin(GL_POINTS);
        glColor3f(r, g, b);
        glVertex2i(x, y);
        // glVertex2i(x*pixelScale+2, y*pixelScale+2);
    glEnd();
}



void graphOutline(vertexObject *vo){
    // Use the shader program
    glUseProgram(vo->shaderProg);

    // Bind the VAO
    glBindVertexArray(vo->VAO);

    // Draw the graph
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    // Unbind the VAO
    glBindVertexArray(0);
}