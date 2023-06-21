#ifndef __PARAMETER_H__
#define __PARAMETER_H__

/* TEST case */
#define TEST_NUM    10000

/* Image feature */
#define IMAGE_SIZE  32 * 32
#define IMAGE_ROW   32
#define IMAGE_COL   32
#define IMAGE_NUM   1

/* Filter feature */
#define WEIGHT_SIZE 25
#define WEIGHT_COL  5
#define WEIGHT_ROW  5

/* Pooling feature */
#define POOL_ROW    2
#define POOL_COL    2
#define POOL_STRIDE 2

/* 1st Convolution layer Output */
#define CONV1_OUTPUT_SIZE   3 * 28 * 28
#define CONV1_OUTPUT_NUM    3
#define CONV1_OUTPUT_ROW    28
#define CONV1_OUTPUT_COL    28

/* 1st Convolution layer Weight & Bias */
#define CONV1_WEIGHT_SIZE   3 * 1 * 5 * 5
#define CONV1_WEIGHT_NUM    3
#define CONV1_WEIGHT_CH     1
#define CONV1_BIAS_SIZE     3

/* 1st Max Pooling layer Output */
#define POOL1_OUTPUT_SIZE   3 * 14 * 14
#define POOL1_OUTPUT_NUM    3
#define POOL1_OUTPUT_ROW    14
#define POOL1_OUTPUT_COL    14

/* 2nd Convolution layer Output */
#define CONV2_OUTPUT_SIZE   6 * 10 * 10
#define CONV2_OUTPUT_NUM    6
#define CONV2_OUTPUT_ROW    10
#define CONV2_OUTPUT_COL    10

/* 2nd Convolution layer Weight & Bias */
#define CONV2_WEIGHT_SIZE   6 * 3 * 5 * 5
#define CONV2_WEIGHT_NUM    6
#define CONV2_WEIGHT_CH     3
#define CONV2_BIAS_SIZE     6

/* 2nd Max Pooling layer Output */
#define POOL2_OUTPUT_SIZE   6 * 5 * 5
#define POOL2_OUTPUT_NUM    6
#define POOL2_OUTPUT_ROW    5
#define POOL2_OUTPUT_COL    5

/* 3th Convolution layer Output */
#define CONV3_OUTPUT_SIZE   12 * 1 * 1
#define CONV3_OUTPUT_NUM    12
#define CONV3_OUTPUT_ROW    1
#define CONV3_OUTPUT_COL    1

/* 3th Convolution layer Weight & Bias */
#define CONV3_WEIGHT_SIZE   12 * 6 * 5 * 5
#define CONV3_WEIGHT_NUM    12
#define CONV3_WEIGHT_CH     6
#define CONV3_BIAS_SIZE     12

/* 1st Fully Connected layer Output */
#define FULL1_OUTPUT_SIZE   10

/* 1st Fully Connected layer Weight */
#define FULL1_WEIGHT_SIZE   12 * 10
#define FULL1_WEIGHT_ROW    10
#define FULL1_WEIGHT_COL    12
#define FULL1_BIAS_SIZE     10

/* 2nd Fully Connected layer Output */
#define FULL2_OUTPUT_SIZE   10

/* 2nd Fully Connected layer Weight */
#define FULL2_WEIGHT_SIZE   10 * 10
#define FULL2_WEIGHT_ROW    10
#define FULL2_WEIGHT_COL    10
#define FULL2_BIAS_SIZE     10

#endif