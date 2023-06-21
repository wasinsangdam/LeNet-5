#ifndef __LAYER_H__
#define __LAYER_H__

#include "type.h"
#include "parameter.h"
#include "weight.h"

void read_input(float* input, input_t output[IMAGE_ROW][IMAGE_COL]);

void conv1_layer(input_t input[IMAGE_ROW][IMAGE_COL], 
                 conv1_t output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL]);

void pool1_layer(conv1_t  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL],
                 conv1_t output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL]);

void conv2_layer(conv1_t  input[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL],
                 conv2_t output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL]);

void pool2_layer(conv2_t  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL],
                 conv2_t output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL]);

void conv3_layer(conv2_t  input[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL],
                 conv3_t output[CONV3_OUTPUT_SIZE]);

void full1_layer(conv3_t  input[CONV3_OUTPUT_SIZE],
                 full1_t output[FULL1_OUTPUT_SIZE]);

void full2_layer(full1_t  input[FULL1_OUTPUT_SIZE],
                 full2_t output[FULL2_OUTPUT_SIZE]);

uint8_t result(full2_t* array);

#endif
