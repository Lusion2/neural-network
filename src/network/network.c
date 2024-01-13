#include <../src/network/network.h>

void LayerInit(Layer *layer, int in, int out){
    layer->nodesIn = in;
    layer->nodesOut = out;

    // memory initialization for weights and biases in the layer
    layer->weights = (double**)malloc(sizeof(double*)*in);
    for(int i = 0; i < in; i++){
        layer->weights[i] = (double*)malloc(sizeof(double)*out);
    }
    layer->biases = (double*)malloc(sizeof(double)*out);
    TEST_LAYER_MEMORY(layer);
}

void LayerFree(Layer *layer){
    // freeing each row of weights in the 2D array
    for(int i = 0; i < layer->nodesIn; i++){
        free(layer->weights[i]);
    }
    // freeing the total weights
    free(layer->weights);
    // freeing the biases
    free(layer->biases);
}