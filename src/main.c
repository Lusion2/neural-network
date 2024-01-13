#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <../src/network/network.h>
// #include <../src/graphics/graphics.h>

// easier than dynamic arrays
#define MAX_LAYER_NODES       2 
#define MAX_IN_NODES    2
#define MAX_OUT_NODES    2

//----------------------------
//
//  INITIAL STRUCTURES FOR
//    THE NEURAL NETWORK
//
//----------------------------

// typedef struct Network{
//     // node will be the input and the weight
//     Node in[MAX_NODES];
//     Node out[MAX_NODES];
// } Network;

// prototype will have 2 inputs and 2 outputs
// the name of the weights here are weight(inputnode),(outputnode)
// output 1 = (in1*weight1,1) + (in2*weight2,1)
// output 2 = (in1*weight1,2) + (in2*weight2,2)

// out1 = pass
// out2 = fail


// Window initialization
// GLFWwindow *win = NULL;


// void TESTGraph(Node *in1, Node *in2, vertexObject *vo);

int main(void){

    Layer layer = {0};
    LayerInit(&layer, 2, 2);
    LayerFree(&layer);

    // time_t t;
    // srand((unsigned) time(&t));

    // win = graphicsInit(win, WIDTH, HEIGHT);

    // vertexObject vo = {0};
    // vertexObjectInit_TEST(&vo);

    // while(!glfwWindowShouldClose(win)){
    //     glClear(GL_COLOR_BUFFER_BIT);

        
    //     TESTGraph(&in1, &in2, &vo);
    //     glfwSwapBuffers(win);
    //     glfwPollEvents();
    // }

    // glfwTerminate();

    // how to do first step
    // network(&in1, &in2);

    return 0;
}

// void TESTGraph(Node *in1, Node *in2, vertexObject *vo){
//     graphOutline(vo);

//     int pass = 0;
//     int fail = 0;
//     for(int x = 0; x < WIDTH; x++){
//         for(int y = 0; y < HEIGHT; y++){
//             in1->val = x;
//             in2->val = y;
//             int a = network(in1, in2);
            
//             // a = 1, therefore pass
//             if(a == 1){
//                 // pixelDraw(x, y, 0.0f, 1.0f, 0.0f);
//                 pass++;
//             } 
//             // a = 2, therefore fail
//             else{
//                 // pixelDraw(x, y, 1.0f, 0.0f, 0.0f);
//                 fail++;
//             }
//         }
//     }
//     printf("PASSED: %i, FAILED: %i\n", pass, fail);
// }