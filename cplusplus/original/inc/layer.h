#ifndef __LAYER_H__
#define __LAYER_H__

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "parameter.h"
#include "weight.h"

void conv1_layer(float* input, 
                 float  output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL]);

void pool1_layer(float  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL], 
                 float output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL]);

void conv2_layer(float  input[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL], 
                 float output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL]);

void pool2_layer(float  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL], 
                 float output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL]);

void conv3_layer(float  input[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL], 
                 float output[CONV3_OUTPUT_SIZE]);

void full1_layer(float  input[CONV3_OUTPUT_SIZE], 
                 float output[FULL1_OUTPUT_SIZE]);

void full2_layer(float  input[FULL2_OUTPUT_SIZE], 
                 float output[FULL2_OUTPUT_SIZE]);

float sigmoid(float x);

uint8_t softmax(float input[FULL2_OUTPUT_SIZE]);



#endif
