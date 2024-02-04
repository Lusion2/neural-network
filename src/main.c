/*
 * Code by Treyse Miller (Lusion2 on Github)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "../src/network/network.h"
// #include <../src/graphics/graphics.h>

//----------------------------
//
//  INITIAL STRUCTURES FOR
//    THE NEURAL NETWORK
//
//----------------------------


// Window initialization
// GLFWwindow *win = NULL;


// void TESTGraph(vertexObject *vo);

int main(void){

    time_t t;
    srand((unsigned)time(&t));

    NeuralNetwork network = {0};
    int layerSize[] = {2, 3, 5, 3, 2, 3};
    double expectedOutputs[] = {0.0f, 0.5f, 1.0f};
    double inputs[] = {2.0f, 6.0f};

    NetworkInit(&network, 6, layerSize, expectedOutputs, inputs);

    printf("Given inputs:\n");
    for(int i = 0; i < layerSize[0]; i++){
        printf("\t%f\n", inputs[i]);
    }

    
    Learn(&network, 500.0f, 10000);

    
    //NetworkPrintOutputs(&network);

    NetworkFree(&network);

    // time_t t;
    // srand((unsigned) time(&t));

    // win = graphicsInit(win, WIDTH, HEIGHT);

    // vertexObject vo = {0};
    // vertexObjectInit(&vo);

    // while(!glfwWindowShouldClose(win)){
    //     glClear(GL_COLOR_BUFFER_BIT);

        
    //     TESTGraph(&vo);
    //     glfwSwapBuffers(win);
    //     glfwPollEvents();
    // }

    // glfwTerminate();

    // how to do first step
    // network(&in1, &in2);

    return 0;
}

// void TESTGraph(vertexObject *vo){
//     graphOutline(vo);
// }