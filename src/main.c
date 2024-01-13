#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <../src/network/network.h>
#include <../src/graphics/graphics.h>

//----------------------------
//
//  INITIAL STRUCTURES FOR
//    THE NEURAL NETWORK
//
//----------------------------


// Window initialization
GLFWwindow *win = NULL;


void TESTGraph(vertexObject *vo);

int main(void){

    NeuralNetwork network = {0};
    int layerSize[] = {2, 3, 2};
    NetworkInit(&network, 2, layerSize);
    
    double inputs[] = {3, 7};

    NetworkCalcOutputs(&network, inputs);

    NetworkFree(&network);

    // time_t t;
    // srand((unsigned) time(&t));

    win = graphicsInit(win, WIDTH, HEIGHT);

    vertexObject vo = {0};
    vertexObjectInit(&vo);

    while(!glfwWindowShouldClose(win)){
        glClear(GL_COLOR_BUFFER_BIT);

        
        TESTGraph(&vo);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();

    // how to do first step
    // network(&in1, &in2);

    return 0;
}

void TESTGraph(vertexObject *vo){
    graphOutline(vo);
}