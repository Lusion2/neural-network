#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

#include <../src/graphics/graphics.h>

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

typedef struct v3{
    int x, y, val;
}v3;

/*
 * Data structure for nodes
 * 
 * Holds the current node value,
 * It's weight for each output,
 * Each of its output nodes, and
 * Each of its input nodes
 */
typedef struct Node Node;
struct Node{
    int val;                        // in is the input value of the node
    uint8_t w[MAX_OUT_NODES];       // w is the weight of the node to the output node
    Node *out[MAX_OUT_NODES];       // linked list for output nodes
    Node *in[MAX_IN_NODES];         // linked list for input nodes
};

/*
 * A node layer
 *
 * Holds a pointer to each of the nodes in a given layer 
 * and a pointer to the next and previous layers
 */
// typedef struct Layer Layer;
// struct Layer{
//     Node *nodes[MAX_LAYER_NODES];
//     Layer *next;
//     Layer *prev;
// };

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
GLFWwindow *win = NULL;


int network(Node *in1, Node *in2);
void TESTinitNode(Node *in1, Node *in2, Node *out1, Node *out2);
void TESTGraph(Node *in1, Node *in2);

int main(void){
    time_t t;
    srand((unsigned) time(&t));

    win = graphicsInit(win, 1280, 720);

    Node in1, in2, out1, out2;
    TESTinitNode(&in1, &in2, &out1, &out2);
    TESTGraph(&in1, &in2);

    // how to do first step
    // network(&in1, &in2);

    return 0;
}

/*
 * do the calculations for the current network
 *
 * in(#) corresponds to the input
 * w(#) corresponds to the weight of each input 
 */
int network(Node *in1, Node *in2){
    in1->out[0]->val = in1->val*in1->w[0] + in2->val*in2->w[0];
    in1->out[1]->val = in1->val*in1->w[1] + in2->val*in2->w[1];
    if (in1->out[0]->val > in1->out[1]->val){
        return 1;
    } else{
        return 0;
    }
}

/*
 * initializing nodes for testing purposes **VERY EARLY VERSION**
 */
void TESTinitNode(Node *in1, Node *in2, Node *out1, Node *out2){
    in1->out[0] = out1;
    in1->out[1] = out2;
    in1->w[0] = 4;
    in1->w[1] = 6;
    // for(int i = 0; i < MAX_OUT_NODES; i++){
        // in1->w[i] = (uint8_t)rand() % 100;
    // }

    in2->out[0] = out1;
    in2->out[1] = out2;
    // for(int i = 0; i < MAX_OUT_NODES; i++){
    //     in2->w[i] = (uint8_t)rand() % 100;
    // }
    in2->w[0] = 8;
    in2->w[1] = 2;
}

void TESTGraph(Node *in1, Node *in2){
    // int as[100][100] = {0}; // for calculation purposes
    int pass = 0;
    int fail = 0;
    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
            in1->val = x;
            in2->val = y;
            int a = network(in1, in2);
            
            // a = 1, therefore pass
            if(a == 1){
                pass++;
            } 
            // a = 2, therefore fail
            else{
                fail++;
            }
        }
    }
    printf("PASSED: %i, FAILED: %i\n", pass, fail);
}