#include <../src/network/network.h>
#include <math.h>
#include <time.h>

double nodeActivation(double wIn){
    // sigmoid function (for now)
    return 1 / (1 + (double)exp(-wIn*0.2f));
}

double nodeCost(double target, double given){
    // quadratic cost funtion
    return 10 * pow(given - target, 2);
}

double cost(NeuralNetwork *network){
    // create a copy of the network passed in in order to calculate the cost of a difference to a weight/bias
    // note, this is slow and probably unnecessary 
    //printf("actual network weight 0, 0: %f\n", network->layers[0].weights[0][0]);
    NetworkCalcOutputs(network);
    double cost = 0;
    // calc the cost of each node in the output layer
    for(int nodeOut = 0; nodeOut < network->layers[network->numLayers-1].nodesOut; nodeOut++){
        cost += nodeCost(network->expectedOutputs[nodeOut], network->outputs[nodeOut]);
    }
    return cost;
}

void GradientDescent(Layer *layer, double learnRate){
    // update the weights and biases of the layer according to the cost gradient
    for(int nodeOut = 0; nodeOut < layer->nodesOut; nodeOut++){
        // update the biases
        layer->biases[nodeOut] -= layer->gradientDescentB[nodeOut] * learnRate;
        //printf("New bias for output, %d: %f\n", nodeOut, layer->biases[nodeOut]);
        for(int nodeIn = 0; nodeIn < layer->nodesIn; nodeIn++){
            layer->weights[nodeIn][nodeOut] = layer->gradientDescentW[nodeIn][nodeOut] * learnRate;
            //printf("New weight for %d, %d: %f\n", nodeIn, nodeOut, layer->weights[nodeIn][nodeOut]);
        }
    }
}

void Learn(NeuralNetwork *network, double learnRate, int iterations){
    for(int i = 0; i < iterations; i++){
        NetworkCalcOutputs(network);
        printf("Iteration %i\n", i);
        NetworkPrintOutputs(network);
        double h = 0.001f;
        double originalCost = cost(network);
        printf("Original cost: %f\n", originalCost);

        for(int i = 0; i < network->numLayers; i++){
            // calculate the cost gradient for the current weights
            for(int nodeIn = 0; nodeIn < network->layers[i].nodesIn; nodeIn++){
                for(int nodeOut = 0; nodeOut < network->layers[i].nodesOut; nodeOut++){
                    // figure out what the cost would be if the weight was slightly increased
                    network->layers[i].weights[nodeIn][nodeOut] += h;
                    double deltaCost = cost(network) - originalCost;
                    //printf("delta cost: %f\n", deltaCost);
                    network->layers[i].weights[nodeIn][nodeOut] -= h;
                    network->layers[i].gradientDescentW[nodeIn][nodeOut] = deltaCost;
                }
            }

            for(int nodeOut = 0; nodeOut < network->layers[i].nodesOut; nodeOut++){
                network->layers[i].biases[nodeOut] += h;
                double deltaCost =  cost(network) - originalCost;
                //printf("%f\n", deltaCost);
                network->layers[i].biases[nodeOut] -= h;
                network->layers[i].gradientDescentB[nodeOut] = deltaCost;
            }
            GradientDescent(&network->layers[i], learnRate);
        }
    }
}

void LayerInit(Layer *layer, int in, int out){
    layer->nodesIn = in;
    layer->nodesOut = out;

    // memory initialization for weights and biases in the layer
    layer->weights = (double**)malloc(sizeof(double*)*in);
    layer->gradientDescentW = (double**)malloc(sizeof(double*)*in);
    for(int i = 0; i < in; i++){
        layer->weights[i] = (double*)malloc(sizeof(double)*out);
        layer->gradientDescentW[i] = (double*)malloc(sizeof(double)*out);
        // this for loop sets random values to the weights, good for now
        for(int j = 0; j < out; j++){
            layer->weights[i][j] = (double)rand()/(RAND_MAX*2.0f);
        }
    }

    layer->biases = (double*)malloc(sizeof(double)*out);
    layer->gradientDescentB = (double*)malloc(sizeof(double)*out);
    layer->vals = (double*)malloc(sizeof(double)*out);
    for(int i = 0; i < out; i++){
        layer->biases[i] = i;
    }
}

void LayerFree(Layer *layer){
    // freeing each row of weights in the 2D array
    for(int i = 0; i < layer->nodesIn; i++){
        free(layer->weights[i]);
        free(layer->gradientDescentW[i]);
    }
    // freeing the total weights
    free(layer->weights);
    // freeing the biases
    free(layer->biases);
    //free  the gradient descents
    free(layer->gradientDescentB);
    free(layer->gradientDescentW);
    free(layer->vals);
}

double *LayerCalcOutputs(Layer *layer, double *inputs){
    double *wInputs = (double*)malloc(sizeof(double)*layer->nodesOut); // weighted inputs
    
    // iterate through each outgoing node
    for(int out = 0; out < layer->nodesOut; out++){
        // initialize a weighted input to the bias value
        double wInput = layer->biases[out];
        // iterate through each incoming node
        for(int in = 0; in < layer->nodesIn; in++){
            // add the weighted input to the input value times the corresponding weight
            wInput += inputs[in] * layer->weights[in][out];
        }
        // check if the weighted input passes the activation function
        wInput = nodeActivation(wInput);

        // set the corresponding spot in the wInputs array to the weighted input we just calculated
        wInputs[out] = wInput;
        layer->vals[out] = wInput;
    }

    // free the inputs for memory leak purposes
    free(inputs);

    return wInputs;
}

void NetworkInit(NeuralNetwork *network, int layers, int *layerSizes, double *expectedOutputs, double *inputs){
    network->numLayers = layers-1;
    network->layerSizes = layerSizes;
    network->layers = (Layer*)malloc(sizeof(Layer)*(layers-1));
    for(int i = 0; i < network->numLayers; i++){
        LayerInit(&network->layers[i], layerSizes[i], layerSizes[i+1]);
    }
    network->expectedOutputs = (double*)malloc(sizeof(double)*layerSizes[network->numLayers]);
    for(int i = 0; i < layerSizes[layers-1]; i++){
        network->expectedOutputs[i] = expectedOutputs[i];
    }
    network->inputs = inputs;
    network->outputs = (double*)malloc(sizeof(double));
}

void NetworkFree(NeuralNetwork *network){
    for(int i = 0; i < network->numLayers; i++){
        LayerFree(&network->layers[i]);
    }
    free(network->layers);
    free(network->outputs);
    free(network->expectedOutputs);
}

void NetworkCalcOutputs(NeuralNetwork *network){
    // using a different variable for memory purposes, makes it easier for the 
    // user of this code to know what is happening to their variables
    double *ins = (double*)malloc(sizeof(double)*network->layers[0].nodesIn);
    for(int i = 0; i < network->layers[0].nodesIn; i++){
        ins[i] = network->inputs[i];
    }

    free(network->outputs);

    // iterate through each layer and calc it's outputs
    // ins gets freed and then set to the outputs of the layer which are 
    // then used as the inputs to the next layer
    for(int i = 0; i < network->numLayers; i++){
        ins = LayerCalcOutputs(&network->layers[i], ins);
    }

    network->outputs = ins;
}

void NetworkPrintOutputs(NeuralNetwork *network){
    printf("Outputs:\n");
    for(int i = 0; i < network->layers[network->numLayers-1].nodesOut; i++){
        printf("\t%f\n", network->outputs[i]);
    }
}