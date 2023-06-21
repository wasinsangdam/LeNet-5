#ifndef __ORIGIN_H__
#define __ORIGIN_H__

#include <cmath>
#include "xil_types.h"
#include "originParam.h"
#include "originWeight.h"


void org_predict(float* input, u8* output);

void org_conv1_layer(float* input, 
                     float  output[ORG_CONV1_OUTPUT_NUM][ORG_CONV1_OUTPUT_ROW][ORG_CONV1_OUTPUT_COL]);

void org_pool1_layer(float  input[ORG_CONV1_OUTPUT_NUM][ORG_CONV1_OUTPUT_ROW][ORG_CONV1_OUTPUT_COL], 
                     float output[ORG_POOL1_OUTPUT_NUM][ORG_POOL1_OUTPUT_ROW][ORG_POOL1_OUTPUT_COL]);

void org_conv2_layer(float  input[ORG_POOL1_OUTPUT_NUM][ORG_POOL1_OUTPUT_ROW][ORG_POOL1_OUTPUT_COL], 
                     float output[ORG_CONV2_OUTPUT_NUM][ORG_CONV2_OUTPUT_ROW][ORG_CONV2_OUTPUT_COL]);

void org_pool2_layer(float  input[ORG_CONV2_OUTPUT_NUM][ORG_CONV2_OUTPUT_ROW][ORG_CONV2_OUTPUT_COL], 
                     float output[ORG_POOL2_OUTPUT_NUM][ORG_POOL2_OUTPUT_ROW][ORG_POOL2_OUTPUT_COL]);

void org_conv3_layer(float  input[ORG_POOL2_OUTPUT_NUM][ORG_POOL2_OUTPUT_ROW][ORG_POOL2_OUTPUT_COL], 
                     float output[ORG_CONV3_OUTPUT_SIZE]);

void org_full1_layer(float  input[ORG_CONV3_OUTPUT_SIZE], 
                     float output[ORG_FULL1_OUTPUT_SIZE]);

void org_full2_layer(float  input[ORG_FULL2_OUTPUT_SIZE], 
                     float output[ORG_FULL2_OUTPUT_SIZE]);

float sigmoid(float x);

void softmax(float input[ORG_FULL2_OUTPUT_SIZE], u8* output);




#endif