#ifndef __REFERENCE_H__
#define __REFERENCE_H__

#include "xil_types.h"
#include "parameter.h"
#include "weight.h"

void predict_ref(float* input, u8* output);

void conv1_layer(float* input, 
                 float  output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL]);

void relu1_layer(float  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL], 
                 float output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL]);

void pool1_layer(float  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL], 
                 float output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL]);

void conv2_layer(float  input[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL], 
                 float output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL]);

void relu2_layer(float  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL], 
                 float output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL]);

void pool2_layer(float  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL], 
                 float output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL]);

void conv3_layer(float  input[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL], 
                 float output[CONV3_OUTPUT_SIZE]);

void relu3_layer(float  input[CONV3_OUTPUT_SIZE], 
                 float output[CONV3_OUTPUT_SIZE]);

void full1_layer(float  input[CONV3_OUTPUT_SIZE], 
                 float output[FULL1_OUTPUT_SIZE]);

void relu4_layer(float  input[FULL1_OUTPUT_SIZE], 
                 float output[FULL1_OUTPUT_SIZE]);

void full2_layer(float  input[FULL2_OUTPUT_SIZE], 
                 float output[FULL2_OUTPUT_SIZE]);

void result(float input[FULL2_OUTPUT_SIZE], u8* output);

#endif