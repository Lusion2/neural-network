#include <../src/network/network.h>

void LayerInit(Layer *layer, int in, int out){
    layer->nodesIn = in;
    layer->nodesOut = out;

    // memory initialization for weights and biases in the layer
    layer->weights = (double**)malloc(sizeof(double*)*in);
    for(int i = 0; i < in; i++){
        layer->weights[i] = (double*)malloc(sizeof(double)*out);
        for(int j = 0; j < out; j++){
            layer->weights[i][j] = i*j+1;
        }
    }
    layer->biases = (double*)malloc(sizeof(double)*out);
    for(int i = 0; i < out; i++){
        layer->biases[i] = i;
    }
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

double *LayerCalcOutputs(Layer *layer, double *inputs){
    double *wInputs = (double*)malloc(sizeof(double)*layer->nodesOut); // weighted inputs
    
    printf("Given inputs:\n");
    for(int i = 0; i < 2; i++){
        printf("\t%f\n", inputs[i]);
    }
    // iterate through each outgoing node
    for(int out = 0; out < layer->nodesOut; out++){
        // initialize a weighted input to the bias value
        double wInput = layer->biases[out];
        // iterate through each incoming node
        for(int in = 0; in < layer->nodesIn; in++){
            // add the weighted input to the input value times the corresponding weight
            wInput += inputs[in] * layer->weights[in][out];
        }
        // set the corresponding spot in the wInputs array to the weighted input we just calculated
        wInputs[out] = wInput;
    }
    printf("Weighted inputs:\n");
    for(int i = 0; i < 2; i++){
        printf("\t%f\n", wInputs[i]);
    }

    free(inputs);
    inputs = wInputs;
    return inputs;
}