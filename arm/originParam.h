#ifndef __ORIGIN_PARAMETER_H__
#define __ORIGIN_PARAMETER_H__

/* Image feature */
#define ORG_IMAGE_SIZE  32 * 32
#define ORG_IMAGE_ROW   32
#define ORG_IMAGE_COL   32
#define ORG_IMAGE_NUM   1

/* Filter feature */
#define ORG_WEIGHT_SIZE 25
#define ORG_WEIGHT_COL  5
#define ORG_WEIGHT_ROW  5

/* Pooling feature */
#define ORG_POOL_ROW    2
#define ORG_POOL_COL    2
#define ORG_POOL_STRIDE 2

/* 1st Convolution layer Output */
#define ORG_CONV1_OUTPUT_SIZE   6 * 28 * 28
#define ORG_CONV1_OUTPUT_NUM    6
#define ORG_CONV1_OUTPUT_ROW    28
#define ORG_CONV1_OUTPUT_COL    28

/* 1st Convolution layer Weight & Bias */
#define ORG_CONV1_WEIGHT_SIZE   6 * 1 * 5 * 5
#define ORG_CONV1_WEIGHT_NUM    6
#define ORG_CONV1_WEIGHT_CH     1
#define ORG_CONV1_BIAS_SIZE     6

/* 1st Max Pooling layer Output */
#define ORG_POOL1_OUTPUT_SIZE   6 * 14 * 14
#define ORG_POOL1_OUTPUT_NUM    6
#define ORG_POOL1_OUTPUT_ROW    14
#define ORG_POOL1_OUTPUT_COL    14

/* 2ed Convolution layer Output */
#define ORG_CONV2_OUTPUT_SIZE   16 * 10 * 10
#define ORG_CONV2_OUTPUT_NUM    16
#define ORG_CONV2_OUTPUT_ROW    10
#define ORG_CONV2_OUTPUT_COL    10

/* 2ed Convolution layer Weight & Bias */
#define ORG_CONV2_WEIGHT_SIZE   16 * 6 * 5 * 5
#define ORG_CONV2_WEIGHT_NUM    16
#define ORG_CONV2_WEIGHT_CH     6
#define ORG_CONV2_BIAS_SIZE     16

/* 2ed Max Pooling layer Output */
#define ORG_POOL2_OUTPUT_SIZE   16 * 5 * 5
#define ORG_POOL2_OUTPUT_NUM    16
#define ORG_POOL2_OUTPUT_ROW    5
#define ORG_POOL2_OUTPUT_COL    5

/* 3th Convolution layer Output */
#define ORG_CONV3_OUTPUT_SIZE   120 * 1 * 1
#define ORG_CONV3_OUTPUT_NUM    120
#define ORG_CONV3_OUTPUT_ROW    1
#define ORG_CONV3_OUTPUT_COL    1

/* 3th Convolution layer Weight & Bias */
#define ORG_CONV3_WEIGHT_SIZE   120 * 16 * 5 * 5
#define ORG_CONV3_WEIGHT_NUM    120
#define ORG_CONV3_WEIGHT_CH     16
#define ORG_CONV3_BIAS_SIZE     120

/* 1st Fully Connected layer Output */
#define ORG_FULL1_OUTPUT_SIZE   84

/* 1st Fully Connected layer Weight */
#define ORG_FULL1_WEIGHT_SIZE   120 * 84
#define ORG_FULL1_WEIGHT_ROW    84
#define ORG_FULL1_WEIGHT_COL    120
#define ORG_FULL1_BIAS_SIZE     84

/* 2ed Fully Connected layer Output */
#define ORG_FULL2_OUTPUT_SIZE   10

/* 2st Fully Connected layer Weight */
#define ORG_FULL2_WEIGHT_SIZE   84 * 10
#define ORG_FULL2_WEIGHT_ROW    10
#define ORG_FULL2_WEIGHT_COL    84
#define ORG_FULL2_BIAS_SIZE     10

#endif