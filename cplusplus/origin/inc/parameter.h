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
#define CONV1_OUTPUT_SIZE   6 * 28 * 28
#define CONV1_OUTPUT_NUM    6
#define CONV1_OUTPUT_ROW    28
#define CONV1_OUTPUT_COL    28

/* 1st Convolution layer Weight & Bias */
#define CONV1_WEIGHT_SIZE   6 * 1 * 5 * 5
#define CONV1_WEIGHT_NUM    6
#define CONV1_WEIGHT_CH     1
#define CONV1_BIAS_SIZE     6

/* 1st Max Pooling layer Output */
#define POOL1_OUTPUT_SIZE   6 * 14 * 14
#define POOL1_OUTPUT_NUM    6
#define POOL1_OUTPUT_ROW    14
#define POOL1_OUTPUT_COL    14

/* 2ed Convolution layer Output */
#define CONV2_OUTPUT_SIZE   16 * 10 * 10
#define CONV2_OUTPUT_NUM    16
#define CONV2_OUTPUT_ROW    10
#define CONV2_OUTPUT_COL    10

/* 2ed Convolution layer Weight & Bias */
#define CONV2_WEIGHT_SIZE   16 * 6 * 5 * 5
#define CONV2_WEIGHT_NUM    16
#define CONV2_WEIGHT_CH     6
#define CONV2_BIAS_SIZE     16

/* 2ed Max Pooling layer Output */
#define POOL2_OUTPUT_SIZE   16 * 5 * 5
#define POOL2_OUTPUT_NUM    16
#define POOL2_OUTPUT_ROW    5
#define POOL2_OUTPUT_COL    5

/* 3th Convolution layer Output */
#define CONV3_OUTPUT_SIZE   120 * 1 * 1
#define CONV3_OUTPUT_NUM    120
#define CONV3_OUTPUT_ROW    1
#define CONV3_OUTPUT_COL    1

/* 3th Convolution layer Weight & Bias */
#define CONV3_WEIGHT_SIZE   120 * 16 * 5 * 5
#define CONV3_WEIGHT_NUM    120
#define CONV3_WEIGHT_CH     16
#define CONV3_BIAS_SIZE     120

/* 1st Fully Connected layer Output */
#define FULL1_OUTPUT_SIZE   84

/* 1st Fully Connected layer Weight */
#define FULL1_WEIGHT_SIZE   120 * 84
#define FULL1_WEIGHT_ROW    84
#define FULL1_WEIGHT_COL    120
#define FULL1_BIAS_SIZE     84

/* 2ed Fully Connected layer Output */
#define FULL2_OUTPUT_SIZE   10

/* 2st Fully Connected layer Weight */
#define FULL2_WEIGHT_SIZE   84 * 10
#define FULL2_WEIGHT_ROW    10
#define FULL2_WEIGHT_COL    84
#define FULL2_BIAS_SIZE     10

#endif