#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <../src/network/network.h>
// #include <../src/graphics/graphics.h>

//----------------------------
//
//  INITIAL STRUCTURES FOR
//    THE NEURAL NETWORK
//
//----------------------------


// Window initialization
// GLFWwindow *win = NULL;


// void TESTGraph(Node *in1, Node *in2, vertexObject *vo);

int main(void){

    NeuralNetwork network = {0};
    int layerSize[] = {2, 3, 2};
    NetworkInit(&network, 2, layerSize);

    NetworkFree(&network);

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