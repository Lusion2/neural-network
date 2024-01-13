/*
 * Defining the network data structures 
 * and prototypes for network functions 
 */
#ifndef __AP_COMPSCI_AI_NETWORK_H
#define __AP_COMPSCI_AI_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/******************
 * DATA STRUCTURES FOR THE NETWORK
 *
 ******************/

/*
 * Base layer structures
 *
 * Holds the number of incoming and outgoing nodes
 * the weights for each connection
 * and the biases for each output
 *
 * This structure is based off of Sebastian Lague on Youtube,
 * https://www.youtube.com/watch?v=hfMk-kjRv4c&t=0s 
 */
typedef struct Layer Layer;
struct Layer{
    int nodesIn, nodesOut;  // The number of nodes in and nodes out
    double **weights;       // 2D array of each of the nodes' weights
    double *biases;         // The biases for each weighted output
};

/*
 * function for initializing a layer
 *
 * layer: a pointer to the layer being initialized
 * in: the number of input nodes
 * out: the number of output nodes
 */
void LayerInit(Layer *layer, int in, int out);

/* 
 * frees the allocated memory in the layer structure
 */
void LayerFree(Layer *layer);


#endif // __AP_COMPSCI_AI_NETWORK_H