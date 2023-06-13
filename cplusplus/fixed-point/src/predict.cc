#include "../inc/predict.h"

uint8_t predict(float* input) {

    input_t input_2d[IMAGE_ROW][IMAGE_COL] = { 0.0 };

    /* Intermediate outputs */
    conv1_t conv1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    conv1_t relu1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    conv1_t pool1_output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0.0 };

    conv2_t conv2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    conv2_t relu2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    conv2_t pool2_output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL] = { 0.0 };

    conv3_t conv3_output[CONV3_OUTPUT_SIZE] = { 0.0 };
    conv3_t relu3_output[CONV3_OUTPUT_SIZE] = { 0.0 };

    full1_t full1_output[FULL1_OUTPUT_SIZE] = { 0.0 };
    full1_t relu4_output[FULL1_OUTPUT_SIZE] = { 0.0 };

    full2_t full2_output[FULL2_OUTPUT_SIZE] = { 0.0 };

    /* Read input */
    read_input(input, input_2d);

    /* 1st convolution layer */
    conv1_layer(input_2d, conv1_output);

    /* 1st ReLU layer */
    relu1_layer(conv1_output, relu1_output);

    /* 1st pooling layer */
    pool1_layer(relu1_output, pool1_output);

    /* 2nd convolution layer */
    conv2_layer(pool1_output, conv2_output);

    /* 2nd ReLU layer */
    relu2_layer(conv2_output, relu2_output);
    
    /* 2nd pooling layer */
    pool2_layer(relu2_output, pool2_output);

    /* 3th convolution layer */
    conv3_layer(pool2_output, conv3_output);

    /* 3th ReLU layer */
    relu3_layer(conv3_output, relu3_output);

    /* 1st fully connected layer */
    full1_layer(relu3_output, full1_output);

    /* 4th ReLU layer */
    relu4_layer(full1_output, relu4_output);

    /* 2nd fully connected layer */
    full2_layer(relu4_output, full2_output);

    /* Return result */
    return result(full2_output);
}
