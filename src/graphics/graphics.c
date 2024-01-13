#include <../src/graphics/graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShaderInit(Shader *shader, const char *vsPath, const char *fsPath){
    // CODE ADAPTED FROM Modern C Programming at:
    // https://moderncprogramming.com/loading-a-glsl-shader-from-file-in-opengl-using-pure-c/ 
    
    // suffixes:
    // vs = vertex shader
    // fs = fragment shader
    
    // basic file reading
    FILE *f_vs;
    FILE *f_fs;
    long size_vs = 0;
    long size_fs = 0;
    char *vs; 
    char *fs;

    // read file for size
    f_vs = fopen(vsPath, "rb");
    if(f_vs == NULL){
        fprintf(stderr, "Error opening vertex shader\n");
        exit(EXIT_FAILURE);
    }
    fseek(f_vs, 0L, SEEK_END);
    size_vs = ftell(f_vs)+1;
    fclose(f_vs);

    // read file for content
    f_vs = fopen(vsPath, "r");
    vs = memset(malloc(size_vs), '\0', size_vs);
    fread(vs, 1, size_vs-1, f_vs);
    fclose(f_vs);

    // repeat this for the fragment shader
    f_fs = fopen(fsPath, "rb");
    if(f_fs == NULL){
        fprintf(stderr, "Error opening fragment shader\n");
        exit(EXIT_FAILURE);
    }
    fseek(f_fs, 0L, SEEK_END);
    size_fs = ftell(f_fs)+1;
    fclose(f_fs);

    // read file for content
    f_fs = fopen(fsPath, "r");
    fs = memset(malloc(size_fs), '\0', size_fs);
    fread(fs, 1, size_vs-1, f_fs);
    fclose(f_fs);


    // compile the vertex shader
    unsigned int ID_vs = glCreateShader(GL_VERTEX_SHADER);
    if(ID_vs == 0){
        printf("COULD NOT LOAD VERTEX SHADER: %s\n", vsPath);
    }

    GLint isCompiled = 0;
    glShaderSource(ID_vs, 1, (const char**)&vs, NULL);
    glCompileShader(ID_vs);
    glGetShaderiv(ID_vs, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        printf("Shader compilation error: %s\n", vsPath);
        glDeleteShader(ID_vs);
        return;
    }
    free(vs);

    // compile the fragment shader
    unsigned int ID_fs = glCreateShader(GL_FRAGMENT_SHADER);
    if(ID_fs == 0){
        printf("COULD NOT LOAD VERTEX SHADER: %s\n", fsPath);
    }

    isCompiled = 0;
    glShaderSource(ID_fs, 1, (const char**)&fs, NULL);
    glCompileShader(ID_fs);
    glGetShaderiv(ID_fs, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        printf("Shader compilation error: %s\n", fsPath);
        glDeleteShader(ID_fs);
        return;
    }
    free(fs);

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, ID_vs);
    glAttachShader(shader->ID, ID_fs);

    glLinkProgram(shader->ID);

    char *infoLog = malloc(1024);
    GLint maxLength = 0;
    GLint isLinked = 0;

    glGetProgramiv(shader->ID, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE) {
        printf("Shader Program Linker Error\n");

        glGetProgramiv(shader->ID, GL_INFO_LOG_LENGTH, &maxLength);
        glGetProgramInfoLog(shader->ID, maxLength, &maxLength, &infoLog[0]);

        printf("%s\n", infoLog);

        glDeleteProgram(shader->ID);

        glDeleteShader(ID_vs);
        glDeleteShader(ID_fs);
        free(infoLog);

        return;
    }

    glDetachShader(shader->ID, ID_vs);
    glDetachShader(shader->ID, ID_fs);

    glDeleteShader(ID_vs);
    glDeleteShader(ID_fs);
    free(infoLog);
}

vertexObject *vertexObjectInit(vertexObject *vo){
    ShaderInit(&vo->shader, "./src/graphics/shaders/base.vs", "./src/graphics/shaders/base.fs");

    // Define the graph data
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    GLint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Create a Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &vo->VAO);
    glGenBuffers(1, &vo->VBO);
    glGenBuffers(1, &vo->EBO);

    // Bind the VAO
    glBindVertexArray(vo->VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vo->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind the VBO and set the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vo->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vo;
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
    glUseProgram(vo->shader.ID);

    // Bind the VAO
    glBindVertexArray(vo->VAO);

    // Draw the graph
    glDrawArrays(GL_TRIANGLES, 0, 4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind the VAO
    glBindVertexArray(0);
}