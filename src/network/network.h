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

/****************************
 *
 *    DATA STRUCTURES AND 
 * FUNCTIONS FOR THE NETWORK
 *
 ****************************/

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
 * Network structure made up of node layers
 */
typedef struct network NeuralNetwork;
struct network{
    Layer *layers;
    int numLayers;
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

/*
 * Calculates the outputs for a given layer
 */
double *LayerCalcOutputs(Layer *layer, double *inputs);

/*
 * Initializes a network with a specified amount of layers
 *
 * network: a pointer the the network being initialized
 * layers: the number of layers in the network
 * layerSizes: stored as [in, out] of each layer
 * 
 * Note, in layerSizes, [in1, out1] for layer 1, [in2 (the same as out1), out2], 
 * in 2 is the same as out1 in this case
 */
void NetworkInit(NeuralNetwork *network, int layers, int *layerSizes);

/*
 * Frees the dynamic memory allocated for the network as well as freeing the 
 * dynamic memory in each layer
 */
void NetworkFree(NeuralNetwork *network);

/*
 * Runs the calculations for the entire network and returns the weighted inputs
 */
double *NetworkCalcOutputs(NeuralNetwork *network, double *inputs);

#endif // __AP_COMPSCI_AI_NETWORK_H